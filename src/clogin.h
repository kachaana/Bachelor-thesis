#ifndef CLOGIN_H
#define CLOGIN_H
#include <QWidget>
#include <QDir>
#include <QMessageBox>
#include <QShortcut>
#include <QLineEdit>
#include <QPushButton>
#include "ia_clogin.h"

namespace Ui {
    class CLogin;
}

class CLogin : public IA_CLogin {
    Q_OBJECT

public:
    CLogin();
    CLogin(const CLogin &other);
    CLogin& operator=(const CLogin &other);

    void setServer(IA_CHTTPReceiver * newServer) {
        _server = newServer;
    }

    QLineEdit               *email;
    QLineEdit               *password;
    QPushButton             *logInButton;

public slots:
    void                     authorizationSuccess();
    void                     on_ButtonLogIn_clicked();
    void                     showLoginFail();

private:
    Ui::CLogin               *_ui;
};

#endif // CLOGIN_H
