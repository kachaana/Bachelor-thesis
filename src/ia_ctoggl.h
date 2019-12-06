#ifndef IA_CTOGGL_H
#define IA_CTOGGL_H
#include <QWidget>
#include <QSystemTrayIcon>
#include "ctimeentrylist.h"

class IA_CToggl : public QWidget
{
    Q_OBJECT
public:
    IA_CToggl(QWidget *parent = nullptr);

    virtual void                    setUsername() = 0;
    virtual void                    setIconStopStart(QSystemTrayIcon * icon) = 0;
    virtual void                    setAction(QAction * action) = 0;
    virtual bool                    getIsStart() const = 0;
    virtual void                    on_ButtonStart_clicked() = 0;
    virtual void                    on_ButtonDes_clicked() = 0;
    virtual void                    on_ButtonSettings_clicked() = 0;
    virtual void                    updateTable() = 0;
    virtual void                    calculate() = 0;
};

#endif // IA_CTOGGL_H
