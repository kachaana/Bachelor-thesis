#include "cwindowapplication.h"
#include "ui_cwindowapplication.h"

CWindowApplication::CWindowApplication() : _ui(new Ui::CWindowApplication),
                                           _isLoginLayout(true) {
    _ui->setupUi(this);
    this->setFixedSize(500,400);
    _togglApp = nullptr;
    _file_manager = new CFileManager();
    _server = new CHTTPReceiver();
    auto availableSize = QGuiApplication::screens().first()->geometry();
    int width = availableSize.width()/2 - QWidget::width()/2;
    int height = availableSize.height()/2 - QWidget::height()/2;
    this->move(width, height);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(_file_manager->getApplicationDirPath() + OFFLINE_ICON));
    _menu = new QMenu(this);
    showWindowAction = new QAction((OPEN_ACTION), this);
    showWindowAction->setData(1);
    startStopAction = new QAction((START_ACTION), this);
    startStopAction->setIcon(QIcon(_file_manager->getApplicationDirPath() +START_ICON));
    exitAction = new QAction((EXIT_ACTION), this);
    logoutAction = new QAction((LOGOUT_ACTION), this);
    logoutAction->setData(2);
    goToWebAction = new QAction((WEB_ACTION), this);
    _menu->addAction(showWindowAction);
    _menu->addSeparator();
    _menu->addAction(goToWebAction);
    _menu->addAction(startStopAction);
    _menu->addSeparator();
    _menu->addAction(exitAction);
    _menu->addAction(logoutAction);
    connect(showWindowAction, SIGNAL(triggered()), this, SLOT(openApp()));
    connect(startStopAction, SIGNAL(triggered()), this, SLOT(showStartStopAction()));
    connect(logoutAction, SIGNAL(triggered()), this, SLOT(logOut()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));
    connect(goToWebAction, SIGNAL(triggered()), this, SLOT(goToWeb()));
    trayIcon->setContextMenu(_menu);
    trayIcon->show();
}

CWindowApplication::CWindowApplication(const CWindowApplication &) : IA_CWindowApplication() {}

CWindowApplication& CWindowApplication::operator=(const CWindowApplication &) {
    return *(new CWindowApplication);
}

CWindowApplication::~CWindowApplication(){
    delete _ui;
    if(_togglApp) delete _togglApp;
    if(_server) delete _server;
    if(_file_manager) delete _file_manager;
}

/*!
 * \brief CWindowApplication::run Starting function.
 */

void CWindowApplication::run(){
    if(_file_manager->tokenAvaliable()){
        showDialogWindow();
    }
    else {
        authorization();
    }
}

/*!
 * \brief CWindowApplication::goToWeb Web site with registration form will be opened.
 */

void CWindowApplication::goToWeb() {
    QDesktopServices::openUrl(QUrl(TOGGL_WEB_URL, QUrl::TolerantMode));
}

/*!
 * \brief CWindowApplication::showStartStopAction Changing icons stop/start view.
 */

void CWindowApplication::showStartStopAction() {
    _togglApp->on_ButtonStart_clicked();
}

/*!
 * \brief CWindowApplication::logOut Log out process.
 */

void CWindowApplication::logOut() {
    _file_manager->removeAllConfFiles();
    if(!_isLoginLayout) {
        _file_manager->removeAllConfFiles();
        _menu->removeAction(logoutAction);
        delete _togglApp;
        authorization();
    }
}

/*!
 * \brief CWindowApplication::exit Exit process.
 */

void CWindowApplication::exit() {
    if(!_isLoginLayout && _togglApp->getIsStart()){
        _togglApp->on_ButtonStart_clicked();
    }
    QCoreApplication::exit();
}

/*!
 * \brief CWindowApplication::openApp Openning a main window if was closed.
 */

void CWindowApplication::openApp() {
    this->show();
}

/*!
 * \brief CWindowApplication::authorization CLogin widget will be added and listening for destruction.
 */

void CWindowApplication::authorization(){
    CLogin *login = new CLogin();
    _ui->verticalLayout->addWidget(login);
    _isLoginLayout = true;
    _menu->removeAction(startStopAction);
    _menu->removeAction(logoutAction);
    connect(login, SIGNAL(destroyed(QObject*)), this, SLOT(showDialogWindow()));
}

/*!
 * \brief CWindowApplication::showDialogWindow Function will add and show Toggl widget to a main window.
 */

void CWindowApplication::showDialogWindow(){
    _isLoginLayout = false;
    startStopAction->setText(START_ACTION);
    _menu->insertAction(goToWebAction, startStopAction);
    _menu->addAction(logoutAction);
    _togglApp = new CToggl();
    _togglApp->setUsername();
    _togglApp->setAction(startStopAction);
    _togglApp->setIconStopStart(trayIcon);
    _ui->verticalLayout->addWidget(_togglApp);
}
