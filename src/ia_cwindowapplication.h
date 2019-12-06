#ifndef IA_CWINDOWAPPLICATION_H
#define IA_CWINDOWAPPLICATION_H

#include <QMainWindow>

class IA_CWindowApplication : public QMainWindow
{
    Q_OBJECT
public:
    IA_CWindowApplication(QWidget *parent = nullptr);

    virtual void                            run() = 0;

public:
    virtual void                            authorization() = 0;
    virtual void                            showDialogWindow() = 0;
    virtual void                            logOut() = 0;
    virtual void                            exit() = 0;
    virtual void                            goToWeb() = 0;
    virtual void                            openApp() = 0;
    virtual void                            showStartStopAction() = 0;
};

#endif // IA_CWINDOWAPPLICATION_H
