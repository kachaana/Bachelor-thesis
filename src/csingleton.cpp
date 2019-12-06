#include "csingleton.h"



CSingleton::CSingleton(int &argc, char **argv) :IA_CSingleton(argc, argv), _is_running(false),
                                                                          _local_server(nullptr) {
    _server_name = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    initLocalConnection();
}


CSingleton& CSingleton::operator=(const CSingleton & sig) {
    this->_is_running = sig.isRunning();
    _server_name = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    initLocalConnection();
    return *this;
}


/*!
 * \brief CSingleton::newLocalConnection Creation of new connection.
 */

void CSingleton::newLocalConnection(){
    QLocalSocket *socket = _local_server->nextPendingConnection();
    if (socket) {
        socket->waitForReadyRead(2 * TIMEOUT_MS);
        delete socket;
        activateWindow();
    }
}

/*!
 * \brief CSingleton::initLocalConnection Function will check for existance of another instances of application.
 *        If any instance doesn't exist, new instance will be created. Overwise returned from the program.
 */

void CSingleton::initLocalConnection(){
    _is_running = false;
    QLocalSocket socket;
    socket.connectToServer(_server_name);
    if (socket.waitForConnected(TIMEOUT_MS)) {
        fprintf(stderr, "%s already running.\n", _server_name.toLocal8Bit().constData());
        _is_running = true;
        return;
    }
    newLocalServer();
}

/*!
 * \brief CSingleton::newLocalServer Initiation of listening to free adresses for local serer.
 */

void CSingleton::newLocalServer(){
    _local_server = new QLocalServer(this);
    connect(_local_server, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));
    if (!_local_server->listen(_server_name)) {
        if (_local_server->serverError() == QAbstractSocket::AddressInUseError) {
            QLocalServer::removeServer(_server_name);
            _local_server->listen(_server_name);
        }
    }
}

/*!
 * \brief CSingleton::activateWindow Activation of main application window.
 */

void CSingleton::activateWindow(){
    if (widget) {
        widget->show();
        widget->raise();
        widget->activateWindow();
    }
}
