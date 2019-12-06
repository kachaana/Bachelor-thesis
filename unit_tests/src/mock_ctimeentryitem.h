#ifndef MOCK_CTIMEENTRYITEM_H
#define MOCK_CTIMEENTRYITEM_H

#include "../../src/ia_ctimeentryitem.h"
#include "test_data.h"

class Mock_CTimeEntryItem : public IA_CTimeEntryItem {
public:
    Mock_CTimeEntryItem();
    QString             timeEntryToJSON();
    int                 getTimeEntryIDFromResponse(QByteArray);

    void setId(const int);
    int getId() const;
};

#endif // MOCK_CTIMEENTRYITEM_H
