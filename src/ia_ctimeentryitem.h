#ifndef IA_CTIMEENTRYITEM_H
#define IA_CTIMEENTRYITEM_H
#include <QString>

class IA_CTimeEntryItem {
public:
    IA_CTimeEntryItem();
    IA_CTimeEntryItem(const QString, const QString);
    virtual ~IA_CTimeEntryItem() = 0;

    virtual QString             timeEntryToJSON() = 0;
    virtual int                 getTimeEntryIDFromResponse(QByteArray) = 0;
    virtual void                setId(const int idNew) = 0;
    virtual int                 getId() const = 0;
};

#endif // IA_CTIMEENTRYITEM_H
