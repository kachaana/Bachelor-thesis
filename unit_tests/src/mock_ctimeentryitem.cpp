#include "mock_ctimeentryitem.h"

Mock_CTimeEntryItem::Mock_CTimeEntryItem() {}

QString Mock_CTimeEntryItem::timeEntryToJSON() {
    return TEST_STRING;
}

int Mock_CTimeEntryItem::getTimeEntryIDFromResponse(QByteArray) {
    return TEST_INT;
}

void Mock_CTimeEntryItem::setId(const int) {}

int Mock_CTimeEntryItem::getId() const {
    return TEST_INT;
}
