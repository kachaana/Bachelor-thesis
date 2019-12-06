#include "testcwidnowapplication.h"

TestCWidnowApplication::TestCWidnowApplication(QObject *parent) : QObject(parent) {
    windowApplication = new CWindowApplication;
    Mock_CToggl * dummyToggl = new Mock_CToggl();
    Mock_CFileManager * dummyFileManager = new Mock_CFileManager();
    Mock_CHttpReceiver * dummyReceiver = new Mock_CHttpReceiver();
    windowApplication->setCToggl(dummyToggl);
    windowApplication->setCFileanager(dummyFileManager);
    windowApplication->setServer(dummyReceiver);
    QApplication::setActiveWindow(windowApplication);
}

void TestCWidnowApplication::testAuthorization() {
    windowApplication->authorization();
    QCOMPARE(windowApplication->getUi()->verticalLayout->itemAt(0)->widget()->metaObject()->className(), "CLogin");
}

void TestCWidnowApplication::testShowDialogWindow() {
    QWidget * login =  windowApplication->getUi()->verticalLayout->itemAt(0)->widget();
    QSignalSpy spy(login, &QObject::destroyed);
    delete login;
    QCOMPARE(spy.count(), 1);
}


void TestCWidnowApplication::testGoToWeb() {
    QSignalSpy spy(windowApplication->goToWebAction, &QAction::triggered);
    windowApplication->goToWebAction->trigger();
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(windowApplication->goToWebAction, SIGNAL(triggered()), windowApplication, SLOT(goToWeb()), Qt::UniqueConnection));
}

void TestCWidnowApplication::testOpenApp() {
    windowApplication->hide();
    QVERIFY(windowApplication->isHidden());
    QSignalSpy spy(windowApplication->showWindowAction, &QAction::triggered);
    windowApplication->showWindowAction->trigger();
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(windowApplication->showWindowAction, SIGNAL(triggered()), windowApplication, SLOT(openApp()), Qt::UniqueConnection));
    QVERIFY(!windowApplication->isHidden());
}

void TestCWidnowApplication::testShowStartStopAction() {
    QCOMPARE(windowApplication->startStopAction->text(), START_ACTION);
    QSignalSpy spy(windowApplication->startStopAction, &QAction::triggered);
    windowApplication->startStopAction->trigger();
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(windowApplication->startStopAction , SIGNAL(triggered()), windowApplication, SLOT(showStartStopAction()), Qt::UniqueConnection));
    QCOMPARE(windowApplication->startStopAction->text(), STOP_ACTION);
}

void TestCWidnowApplication::testLogOut() {
    QCOMPARE(windowApplication->getUi()->verticalLayout->itemAt(0)->widget()->metaObject()->className(), "CToggl");
    windowApplication->logOut();
    QCOMPARE(windowApplication->getUi()->verticalLayout->itemAt(0)->widget()->metaObject()->className(), "CLogin");
    windowApplication->showDialogWindow();
}

void TestCWidnowApplication::testExit() {
    QSignalSpy spy(windowApplication->exitAction, &QAction::triggered);
    windowApplication->exitAction->trigger();
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(windowApplication->exitAction, SIGNAL(triggered()), windowApplication, SLOT(exit()), Qt::UniqueConnection));
}
