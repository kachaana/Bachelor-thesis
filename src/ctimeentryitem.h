#ifndef CTIMEENTRYITEM_H
#define CTIMEENTRYITEM_H
#include <QDebug>
#include "ia_ctimeentryitem.h"

class CTimeEntryItem : public IA_CTimeEntryItem{
public:
    CTimeEntryItem();
    CTimeEntryItem(const QString, const QString);

    QString             timeEntryToJSON();
    int                 getTimeEntryIDFromResponse(QByteArray);

    void setId(const int idNew) {
        _id = idNew;
    }

    int getId() const {
       return _id;
    }

private:
    int                 _id;
    QString             _description;
    QString             _start;
    QString             _duronly;
};
#endif // CTIMEENTRYITEM_H
