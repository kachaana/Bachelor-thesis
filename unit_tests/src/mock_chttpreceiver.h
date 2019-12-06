#ifndef MOCK_CHTTPRECEIVER_H
#define MOCK_CHTTPRECEIVER_H

#include <QObject>
#include "../../src/ia_chttpreceiver.h"
#include "../../src/ia_ctimeentryitem.h"
#include "test_data.h"

class Mock_CHttpReceiver : public IA_CHTTPReceiver
{
    Q_OBJECT
public:
    Mock_CHttpReceiver();
    void                        sendRequest(IA_CTimeEntryItem *, Action);
    void                        setTimeEntryItem(IA_CTimeEntryItem * const);
    void                        authentication(const QString, const QString);
    int                         HTTPStatusCode(QNetworkReply *);

public slots:
    void                        replyFinished();
    void                        replyClientDetailsFinished();

signals:
    void                        authenticationSuccess() ;
};

#endif // MOCK_CHTTPRECEIVER_H
