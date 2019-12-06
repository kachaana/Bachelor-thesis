#ifndef IA_CLOGIN_H
#define IA_CLOGIN_H
#include <QWidget>
#include "chttpreceiver.h"


class IA_CLogin : public QWidget
{
    Q_OBJECT
public:
    explicit IA_CLogin(QWidget *parent = nullptr);
    ~IA_CLogin();

public:
    virtual void                     authorizationSuccess() = 0;
    virtual void                     on_ButtonLogIn_clicked() = 0;

protected:
    bool                            _is_logged;
    IA_CHTTPReceiver               *_server;
};

#endif // IA_CLOGIN_H
