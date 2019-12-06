#include "clogin.h"
#include "ui_clogin.h"


CLogin::CLogin() : _ui(new Ui::CLogin) {
    _ui->setupUi(this);
    _is_logged = false;
    _server = new CHTTPReceiver();
    _ui->labelLink->setText(REGISTRATION_LINK);
    _ui->labelLink->setTextInteractionFlags(Qt::TextBrowserInteraction);
    _ui->labelLink->setOpenExternalLinks(true);
    connect(_server, SIGNAL(authenticationSuccess()), this, SLOT(authorizationSuccess()));
    connect(_server, SIGNAL(authFail()), this, SLOT(showLoginFail()));
    email = _ui->LineEditUsername;
    password = _ui->LineEditPassword;
    password->setEchoMode(QLineEdit::Password);
    logInButton = _ui->ButtonLogIn;
}


CLogin::CLogin(const CLogin &) : IA_CLogin()  {}

CLogin& CLogin::operator=(const CLogin &) {
    this->_ui->setupUi(this);
    connect(_server, SIGNAL(authenticationSuccess()), this, SLOT(authorizationSuccess()));
    return *this;
}


/*!
 * \brief Interaction with "LogIn" button initiate running of on_pushButton_clicked function.
 *        Will be triggered CHTTPReveiver function authenticateion with user's credentials.
 * *
 */

void CLogin::on_ButtonLogIn_clicked(){
   QString USER = _ui->LineEditUsername->text();
   QString PASSWORD = _ui->LineEditPassword->text();
   _server->authentication(USER, PASSWORD);
//    _server->authentication("nastya.kachan.1996@gmail.com","testtesttest" );
}

/*!
 * \brief Check credentials, shows Fail message in case of wrong credentials.
 */

void CLogin::authorizationSuccess(){
    this->hide();
    _is_logged = true;
    this->~CLogin();
}

/*!
 * \brief Function shows window with "Fail" message is login was failed.
 */

void CLogin::showLoginFail(){
    QMessageBox msgBox;
    msgBox.setWindowTitle(TITLE);
    msgBox.setFixedSize(1000, 1000);
    msgBox.setText(LOGIN_MESSAGE_FAIL);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int res = msgBox.exec();
    if (res == QMessageBox::Ok)
        msgBox.close();
    _ui->LineEditPassword->clear();
}
