#ifndef CSINGLETON_H
#define CSINGLETON_H
#include <QApplication>
#include <QtNetwork/QLocalSocket>
#include <QFileInfo>
#include <QtNetwork/QLocalServer>
#include <QWidget>
#include "data.h"
#include "ia_csingleton.h"

class CSingleton : public IA_CSingleton {
    Q_OBJECT

public:
     CSingleton() {}
     CSingleton(int &argc, char **argv);
     CSingleton(const CSingleton &) : IA_CSingleton() {}
     CSingleton& operator=(const CSingleton &);

     bool isRunning() const {
         return _is_running;
     }

     QWidget                       *widget;

     QLocalServer * getLocalServer() const {
         return _local_server;
     }

private slots:
    void                            newLocalConnection();

private:
    void                            initLocalConnection();
    void                            activateWindow();
    void                            newLocalServer();
    bool                            _is_running;
    QLocalServer                   *_local_server;
    QString                         _server_name;
};

#endif // CSINGLETON_H

