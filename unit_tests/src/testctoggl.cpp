#include "testctoggl.h"

TestCToggl::TestCToggl(QObject *parent) : QObject(parent) {
    toggl = new CToggl();
    Mock_CSettingsMenu * dummySettingsMenu = new Mock_CSettingsMenu();
    Mock_CFileManager * dummyFileManager = new Mock_CFileManager();
    dummyEntryList = new Mock_CTimeEntryList();
    toggl->setSettingsMenu(dummySettingsMenu);
    toggl->setFileManager(dummyFileManager);
    toggl->setTimeEntryList(dummyEntryList);
    toggl->iconsAvailable = false;
    QApplication::setActiveWindow(toggl);
}

void TestCToggl::testSetUsername() {
    toggl->userNameLabel->setFocus();
    QVERIFY(toggl->userNameLabel->hasFocus());
    QCOMPARE(toggl->userNameLabel->text(), "");
    toggl->setUsername();
    QCOMPARE(toggl->userNameLabel->text(), "Hello, " + TEST_USER_NAME + "!");
}

void TestCToggl::testOn_ButtonStart_clicked() {
    QVERIFY(toggl->getIsStart());
    QSignalSpy spy(toggl->buttonStart, &QPushButton::clicked);
    toggl->buttonStart->click();
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(toggl->buttonStart , SIGNAL(clicked()), toggl, SLOT(on_ButtonStart_clicked()), Qt::UniqueConnection));
}

void TestCToggl::testOn_ButtonSettings_clicked() {
    toggl->buttonSet->setFocus();
    QVERIFY(toggl->buttonSet->hasFocus());
    QSignalSpy spy(toggl->buttonSet, &QPushButton::clicked);
    toggl->buttonSet->click();
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(toggl->buttonSet , SIGNAL(clicked()), toggl, SLOT(on_ButtonSettings_clicked()), Qt::UniqueConnection));
}

void TestCToggl::testOn_ButtonDes_clicked() {
    toggl->buttonDes->setFocus();
    QVERIFY(toggl->buttonDes->hasFocus());
    QSignalSpy spy(toggl->buttonDes, &QPushButton::clicked);
    toggl->buttonDes->click();
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(toggl->buttonDes , SIGNAL(clicked()), toggl, SLOT(on_ButtonDes_clicked()), Qt::UniqueConnection));
}

void TestCToggl::testUpdateTable() {
    TIMER_M_SEC = 1000;
    RET_TRUE_FALSE = false;
    QSignalSpy spy(toggl->getTimerTable(), &QTimer::timeout);
    toggl->on_ButtonStart_clicked();
    QVERIFY(spy.wait(TIMER_M_SEC * 2));
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(toggl->getTimerTable() , SIGNAL(timeout()), toggl, SLOT(updateTable()), Qt::UniqueConnection));
    TIMER_M_SEC = 6000;
}


void TestCToggl::testCalculate() {
    QSignalSpy spy(toggl->getTimeEntryList(), SIGNAL(valueChanged()));
    dummyEntryList->emitSignalValueChanged();
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(toggl->getTimeEntryList(), SIGNAL(valueChanged()), toggl, SLOT(calculate()), Qt::UniqueConnection));
}
