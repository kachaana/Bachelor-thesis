
#ifndef CWINDOWAPPLICATION_H
#define CWINDOWAPPLICATION_H
#include <QMainWindow>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QScreen>
#include "clogin.h"
#include "ctoggl.h"
#include "ia_cwindowapplication.h"

namespace Ui {
    class CWindowApplication;
}

class CWindowApplication : public IA_CWindowApplication {
    Q_OBJECT

public:
    CWindowApplication();
    ~CWindowApplication();
    CWindowApplication(const CWindowApplication &other);
    CWindowApplication& operator=(const CWindowApplication &other);

    void                            run();

    Ui::CWindowApplication *getUi () const {
        return _ui;
    }

    QSystemTrayIcon *getTryIcon() const {
        return trayIcon;
    }

    void setCToggl(IA_CToggl * dummyToggl) {
        if(_togglApp) delete _togglApp;
        _togglApp = dummyToggl;
    }

    void setCFileanager(IA_CFileManager * dummyFileManager) {
        if(_file_manager) delete _file_manager;
        _file_manager = dummyFileManager;
    }

    void setServer(IA_CHTTPReceiver * dummyReceiver) {
        if(_server) delete _server;
        _server = dummyReceiver;
    }

    QSystemTrayIcon                *trayIcon;
    QAction                        *startStopAction;
    QAction                        *logoutAction;
    QAction                        *showWindowAction;
    QAction                        *exitAction;
    QAction                        *goToWebAction;

public slots:
    void                            authorization();
    void                            showDialogWindow();
    void                            logOut();
    void                            exit();
    void                            goToWeb();
    void                            openApp();
    void                            showStartStopAction();

private:
    Ui::CWindowApplication         *_ui;
    IA_CToggl                      *_togglApp;
    IA_CFileManager                *_file_manager;
    IA_CHTTPReceiver               *_server;
    QString                         _username;
    bool                            _isLoginLayout;
    QMenu                          *_menu;
};

#endif // CWINDOWAPPLICATION_H
