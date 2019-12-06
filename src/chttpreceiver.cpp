#include "chttpreceiver.h"

CHTTPReceiver::CHTTPReceiver() {
    _manager      = new QNetworkAccessManager();
    _file_manager = new CFileManager();
    _file_manager->getTokenFromFile(_token);
}

CHTTPReceiver::~CHTTPReceiver() {}

CHTTPReceiver::CHTTPReceiver(const CHTTPReceiver& other) {
    _token = other.getToken();
}

CHTTPReceiver& CHTTPReceiver::operator=(const CHTTPReceiver& other) {
    _token = other.getToken();
    return *this;
}

/*!
 * \brief CHTTPReceiver::HTTPStatusCode Function returns standard HTTP response code.
 * \param reply QNetworkReply object that contains reply-body and HTTP status code.
 * \return True is request returns code 200 - OK. False overwise.
 */

int CHTTPReceiver::HTTPStatusCode(QNetworkReply * reply) {
    return reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toInt();
}

/*!
 * \brief CHTTPReceiver::replyClientDetailsFinished Function slot will be called after sending user's credentials and
 *        _reply attribute is loaded. Function emit authenticationSuccess() signal if case of success authorization.
 */

void CHTTPReceiver::replyClientDetailsFinished() {
    int code = HTTPStatusCode(reply);
    if(reply->bytesAvailable() && code == HTTP_OK){
         QByteArray bytesRecieved = reply->readAll();
         _file_manager->uploadTokenToFile(bytesRecieved);
         _file_manager->getTokenFromFile(_token);
         _file_manager->saveNameToFile(getNameFromReply(bytesRecieved));
         emit authenticationSuccess();
    } else {
         emit authFail();
    }
}

/*!
 * \brief CHTTPReceiver::getNameFromReply Function parses reply body and extract user's name.
 * \param reply Array with contained data from reply object.
 * \return User's name in QByteArray format.
 */

QByteArray CHTTPReceiver::getNameFromReply(QByteArray reply) {
    QByteArray idBeg("fullname");
    QByteArray idEnd("jquery_timeofday_format");
    int index = reply.indexOf(idBeg) + 11;
    int indexEnd = reply.indexOf(idEnd) - 3;
    if(index == -1 || indexEnd == -1) {
        qDebug() << "Something went wrong. Please try to log out and log in again.";
        return DEFAULT_USER_NAME.toUtf8();
    }
    QByteArray ret = reply.mid(index, indexEnd - index);
    return ret;
}

/*!
 * \brief CHTTPReceiver::authentication Function will authenticate user with given credentials.
 * \param email User's email.
 * \param password User's password.
 */

void CHTTPReceiver::authentication(const QString email, const QString password) {
    QNetworkRequest request;
    request.setRawHeader("Authorization", "Basic " +
                         QByteArray(QString("%1:%2").arg(email).arg(password).toUtf8()).toBase64());
    request.setUrl(QUrl(AUTH_URL));
    reply = _manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(replyClientDetailsFinished()));
}

/*!
 * \brief CHTTPReciever::sendRequest Function will send request to server for start/stop time entry.
 * \param entry CTimeEntryItem object decribes one time entry.
 * \param act Enum value for control function logic (e.x. can be STOP or START).
 */

void CHTTPReceiver::sendRequest(IA_CTimeEntryItem * entry,  Action act){
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Basic " +
         QByteArray(QString("%1:%2").arg(_token).arg(API_TOKEN).toUtf8()).toBase64());
    switch(act){
    case Action::START: {
        QUrl url(TIME_ENTRY_DETAILS_URL + START_ENTRY);
        request.setUrl(url);
        _actual_request_body = entry->timeEntryToJSON();
        reply = _manager->post(request, _actual_request_body.toUtf8());
        _item = entry;
        connect (reply, SIGNAL(finished()), this, SLOT(replyFinished()));
        break;
    }
    case Action::STOP:{
        int id = entry->getId();
        QString link = TIME_ENTRY_DETAILS_URL + "/" + QString::number(id) + "/stop";
        _actual_request_body = QTime::currentTime().toString();
        request.setUrl(QUrl(link));
        reply = _manager->put(request, "");
        connect (reply, SIGNAL(finished()), this, SLOT(replyFinished()));
        break;
    }
    default: break;
    }
 }

/*!
 * \brief CHTTPReceiver::replyFinished Will be called once reply object is ready to proceed.
 */

void CHTTPReceiver::replyFinished(){
    if(reply->bytesAvailable() && HTTPStatusCode(reply)){
            QByteArray bytesRecieved = reply->readAll();
            _item->setId(_item->getTimeEntryIDFromResponse(bytesRecieved));
    } else {
       qDebug() << "Something wrong with internet connection.";
    }
}

