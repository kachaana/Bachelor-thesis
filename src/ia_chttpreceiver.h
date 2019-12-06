#ifndef IA_CHTTPRECEIVER_H
#define IA_CHTTPRECEIVER_H
#include <QNetworkReply>
#include <QObject>
#include "ctimeentryitem.h"

class IA_CHTTPReceiver : public QObject
{
    Q_OBJECT
    Q_ENUMS(Action)

public:
    enum Action { START, STOP, SYNCH };
    virtual void                        sendRequest(IA_CTimeEntryItem *, Action) = 0;
    virtual void                        setTimeEntryItem(IA_CTimeEntryItem * const) = 0;
    virtual void                        authentication(const QString, const QString) = 0;
    virtual int                         HTTPStatusCode(QNetworkReply *) = 0;
};

#endif // IA_CHTTPRECEIVER_H
