#ifndef IA_CTIMEENTRYLIST_H
#define IA_CTIMEENTRYLIST_H
#include <qtextstream.h>
#include <qstyleoption.h>
#include <QWidget>
#include <QTime>
#include <QX11Info>
#include <QDebug>
#include <QTimer>
#include "chttpreceiver.h"
#include <X11/Xmu/WinUtil.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>
#include "ctablemodel.h"

class IA_CTimeEntryList : public QWidget {
    Q_OBJECT
public:
    explicit IA_CTimeEntryList(QWidget *parent = nullptr);
    ~IA_CTimeEntryList();

    virtual char                        *get_property (Display *, Window, Atom, char *, unsigned long *) = 0;
    virtual int                          getNumberOfDesktops() = 0;
    virtual int                          getCurrentDesktop() = 0;
    virtual void                         setTimeEntryItem(IA_CTimeEntryItem * newTimeEntryItem) = 0;
    virtual IA_CTimeEntryItem           *getTimeEntryItem() const = 0;
    virtual void                         setIsStart(const bool state ) = 0;
    virtual bool                         getIsStart() const = 0;

    QTimer                              *timer;
    QVector<QPair<int,int>>              vectorTime;
    QTime                                timeStart;
    IA_CHTTPReceiver                    *server;
    IA_CTableModel                      *tableModel;

public:
     virtual  void                        detectDesktopsProperty() = 0;
     virtual  void                        decrementTotalDesktopsNumber() = 0;

protected:
    IA_CTimeEntryItem                   *_timeEntryItem;
    IA_CFileManager                     *_fileManager;
};

#endif // IA_CTIMEENTRYLIST_H
