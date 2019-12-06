#ifndef CHTTPRECIEVER_H
#define CHTTPRECIEVER_H
#include <QUrl>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QDebug>
#include <QDialog>
#include "ctimeentryitem.h"
#include "cfilemanager.h"
#include "ia_chttpreceiver.h"

class CHTTPReceiver : public IA_CHTTPReceiver {
    Q_OBJECT

public:
    CHTTPReceiver();
    ~CHTTPReceiver();
    CHTTPReceiver(const CHTTPReceiver &other);
    CHTTPReceiver& operator=(const CHTTPReceiver &other);

    void                        sendRequest(IA_CTimeEntryItem *, Action);
    void                        authentication(const QString, const QString);
    int                         HTTPStatusCode(QNetworkReply *);

    void setTimeEntryItem(IA_CTimeEntryItem * const newItem) {
        _item = newItem;
    }

    QString getToken() const {
        return  _token;
    }

    QNetworkReply              *reply;

public slots:
    void                        replyFinished();
    void                        replyClientDetailsFinished();

private:
    QByteArray                  getNameFromReply(QByteArray);

signals:
    void                        authenticationSuccess();
    void                        authFail();

private:
    QNetworkAccessManager      *_manager;
    IA_CFileManager            *_file_manager;
    IA_CTimeEntryItem          *_item;
    QString                     _actual_request_body;
    QString                     _token;
};

#endif // CHTTPRECIEVER_H
