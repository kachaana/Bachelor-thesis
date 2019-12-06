#include "testclogin.h"



TestCLogin::TestCLogin(QObject *parent) : QObject(parent) {}

void TestCLogin::TimeOut()
{
    QWidgetList allToplevelWidgets = QApplication::topLevelWidgets();
    foreach (QWidget *w, allToplevelWidgets) {
        if (w->inherits("QMessageBox")) {
            QMessageBox *mb = qobject_cast<QMessageBox *>(w);
            QTest::keyClick(mb, Qt::Key_Enter);
        }
    }
}

void TestCLogin::testShowLoginFail() {
    CLogin login;
    QTimer::singleShot(500, this, SLOT(TimeOut()));
    login.showLoginFail();
}

void TestCLogin::testAuthorizationSuccess() {
    QPointer<CLogin> l = new CLogin;
    QVERIFY(!l.isNull());
    l->authorizationSuccess();
    QVERIFY(l.isNull());
}

void TestCLogin::testOn_ButtonLogIn_clicked() {
    Mock_CHttpReceiver * dummyReceiver = new Mock_CHttpReceiver();
    CLogin login;
    login.setServer(dummyReceiver);
    QSignalSpy spy(login.logInButton, &QPushButton::clicked);
    login.logInButton->click();
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(login.logInButton, SIGNAL(clicked()), &login, SLOT(on_ButtonLogIn_clicked()), Qt::UniqueConnection));
}

void TestCLogin::testGUI() {
   Mock_CHttpReceiver * dummyReceiver = new Mock_CHttpReceiver();
   CLogin login;
   login.setServer(dummyReceiver);

   QString em = "abcd";
   QString ps = "efgh";

   QApplication::setActiveWindow(&login);
   login.email->setFocus();
   QVERIFY(login.email->hasFocus());
   QTest::keyClicks(QApplication::focusWidget(), em);
   QCOMPARE(login.email->text(), em);
   login.password->setFocus();
   QVERIFY(login.password->hasFocus());
   QTest::keyClicks(QApplication::focusWidget(), ps);
   QCOMPARE(login.password->text(), ps);
   login.logInButton->setFocus();
   QVERIFY(login.logInButton->hasFocus());
   QTest::keyClick(QApplication::focusWidget(), Qt::Key_Space);
 }

