
#include "ctimeentryitem.h"

CTimeEntryItem::CTimeEntryItem() {}

CTimeEntryItem::CTimeEntryItem(const QString desc, const QString dnl) : _description(desc), _duronly(dnl) {}


/*!
 * \brief CTimeEntryItem::timeEntryToJSON generate JSON-body based on item's attributes.
 * \return JSON-body for http request.
 */

QString CTimeEntryItem::timeEntryToJSON() {
    QString resol("");
    resol += "{\"time_entry\":{";
    resol += "\"description\":\"" + _description + "\",";
    resol += "\"created_with\":\"toggl_client_desk\"," ;
    resol += "\"duronly\":" + _duronly;
    resol += "}}";
    return resol;
}

/*!
 * \brief CTimeEntryItem::getTimeEntryIDFromResponse will parse bytearray from http response and find there item's id.
 * \param byteArray JSON-body of http response.
 * \return item's id in QString format.
 */

int CTimeEntryItem::getTimeEntryIDFromResponse(QByteArray byteArray) {
    QString str = "";
    int ret = -1;
    bool ok;
    QByteArray idBeg("\"id");
    QByteArray idEnd(",");
    int index = byteArray.indexOf(idBeg);
    int indexEnd = byteArray.indexOf(idEnd, index);
    QByteArray tmp = byteArray.mid(index + 5, indexEnd - index - 5);
    QString s(tmp);
    ret = s.toInt(&ok, 10);
    if(ok)
        return ret;
    return -1;
}


