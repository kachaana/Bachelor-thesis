#include "mock_ctimeentrylist.h"
#include "../bin/ui_ctimeentrylist.h"

Mock_CTimeEntryList::Mock_CTimeEntryList() : _ui(new Ui::CTimeEntryList) {
   _fileManager = new Mock_CFileManager;
   _timeEntryItem = new Mock_CTimeEntryItem;
   server = new Mock_CHttpReceiver;
   tableModel = new Mock_CTableModel;
   _ui->setupUi(this);
   int i = 0;
   for (int j = 0; j < 10; j++) {
       QPair<int,int> pair;
       pair.first = i;
       pair.second = i;
       vectorTime.append(pair);
       i++;
   }
}

char * Mock_CTimeEntryList::get_property (Display *, Window, Atom, char *, unsigned long *) {
    return nullptr;
}

int Mock_CTimeEntryList::getNumberOfDesktops() {
    return TEST_NUMBER_OF_DESKTOPS;
}

int Mock_CTimeEntryList::getCurrentDesktop() {
    return TEST_CURRENT_DESKTOPS;
}

void Mock_CTimeEntryList::setTimeEntryItem(IA_CTimeEntryItem * ) {}

IA_CTimeEntryItem * Mock_CTimeEntryList::getTimeEntryItem() const {
    return new Mock_CTimeEntryItem();
}

void Mock_CTimeEntryList::setIsStart(const bool) {}

bool Mock_CTimeEntryList::getIsStart() const {
    return RET_TRUE_FALSE;
}

void Mock_CTimeEntryList::detectDesktopsProperty() {}

void Mock_CTimeEntryList::decrementTotalDesktopsNumber() {}

void Mock_CTimeEntryList::emitSignalValueChanged() {
    emit valueChanged();
}
