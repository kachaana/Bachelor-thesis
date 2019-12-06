#ifndef IA_CSINGLETON_H
#define IA_CSINGLETON_H
#include <QApplication>
#include <QLocalServer>

class IA_CSingleton : public QApplication{
public:
    IA_CSingleton();
    IA_CSingleton(int &argc, char **argv);

protected:
    virtual void                            initLocalConnection() = 0;
    virtual void                            activateWindow() = 0;
    virtual void                            newLocalServer() = 0;
};

#endif // IA_CSINGLETON_H
