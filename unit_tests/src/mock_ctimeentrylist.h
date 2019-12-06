#ifndef MOCK_CTIMEENTRYLIST_H
#define MOCK_CTIMEENTRYLIST_H
#include <QObject>
#include "../../src/ia_ctimeentrylist.h"
#include "../../src/ctimeentrylist.h"
#include "mock_cfilemanager.h"
#include "mock_ctimeentryitem.h"
#include "mock_chttpreceiver.h"
#include "mock_ctablemodel.h"
#include "test_data.h"


namespace Ui {
    class CTimeEntryList;
}

class Mock_CTimeEntryList : public IA_CTimeEntryList {
    Q_OBJECT
public:
    Mock_CTimeEntryList();
    char                        *get_property (Display *, Window, Atom, char *, unsigned long *);
    int                          getNumberOfDesktops();
    int                          getCurrentDesktop();
    void                         setTimeEntryItem(IA_CTimeEntryItem * newTimeEntryItem);
    IA_CTimeEntryItem           *getTimeEntryItem() const ;
    void                         setIsStart(const bool state );
    bool                         getIsStart() const ;
    void                         emitSignalValueChanged();

public slots:
     void                        detectDesktopsProperty();
     void                        decrementTotalDesktopsNumber();

signals:
     void                        valueChanged();

private:
      Ui::CTimeEntryList        *_ui;
};

#endif // MOCK_CTIMEENTRYLIST_H
