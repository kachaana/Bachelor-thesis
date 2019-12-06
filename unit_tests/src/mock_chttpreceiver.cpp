#include "mock_chttpreceiver.h"

Mock_CHttpReceiver::Mock_CHttpReceiver(){}

void Mock_CHttpReceiver::sendRequest(IA_CTimeEntryItem *, Action) {}

void Mock_CHttpReceiver::setTimeEntryItem(IA_CTimeEntryItem * const) {}

void Mock_CHttpReceiver::authentication(const QString, const QString) {}

void Mock_CHttpReceiver::replyFinished() {}

int Mock_CHttpReceiver::HTTPStatusCode(QNetworkReply *) {
    return RET_TRUE_FALSE;
}

void Mock_CHttpReceiver::replyClientDetailsFinished() {}
