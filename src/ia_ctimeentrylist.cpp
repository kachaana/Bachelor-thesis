#include "ia_ctimeentrylist.h"

IA_CTimeEntryList::IA_CTimeEntryList(QWidget *parent) : QWidget(parent) {}

IA_CTimeEntryList::~IA_CTimeEntryList() {
    if(timer) delete timer;
}

