#ifndef CTIMEENTRYLIST_H
#define CTIMEENTRYLIST_H
//#include <chrono>
#include "ia_ctimeentrylist.h"


namespace Ui {
    class CTimeEntryList;
}

class CTimeEntryList : public IA_CTimeEntryList {
    Q_OBJECT

public:
    CTimeEntryList();
    ~CTimeEntryList();

    char                        *get_property (Display *, Window, Atom, char *, unsigned long *);
    int                          getNumberOfDesktops();
    int                          getCurrentDesktop();

    void setTimeEntryItem(IA_CTimeEntryItem * newTimeEntryItem) {
        _timeEntryItem = newTimeEntryItem;
    }

    IA_CTimeEntryItem * getTimeEntryItem() const {
        return _timeEntryItem;
    }

    void setIsStart(const bool state ){
        _isStart = state;
    }

    bool getIsStart() const {
        return _isStart;
    }


public slots:
      void                        detectDesktopsProperty();
      void                        decrementTotalDesktopsNumber();

signals:
      void                        valueChanged();

private:
    Ui::CTimeEntryList           *_ui;
    void                          _initializeList();
    int                           _totalNumberOfDesktops;
    int                           _currentDisplay;
    bool                          _isStart;
    QDate                         _dateEvaluate;
};

#endif // CTIMEENTRYLIST_H
