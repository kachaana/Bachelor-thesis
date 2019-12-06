#include "testcsettingsmenu.h"

TestCSettingsMenu::TestCSettingsMenu(QObject *parent) : QObject(parent) {
    settingsMenu = new CSettingsMenu();
    Mock_CFileManager * dummyFileManager = new Mock_CFileManager();
    settingsMenu->setFileManager(dummyFileManager);
    QApplication::setActiveWindow(settingsMenu);
}

/*
 *  array_check_box[0] = _ui->checkBoxAutorun;
 *  array_check_box[1] = _ui->checkBoxOfflineMode;
 *  array_check_box[2] = _ui->checkBoxReminder;
 *
 */


void TestCSettingsMenu::testOn_checkBoxAutorun_stateChanged() {
    QApplication::setActiveWindow(settingsMenu);
    settingsMenu->array_check_box[0]->setFocus();
    QVERIFY(settingsMenu->array_check_box[0]->hasFocus());
    QSignalSpy spy(settingsMenu->array_check_box[0], &QCheckBox::stateChanged);
    QVERIFY(!settingsMenu->array_check_box[0]->isChecked());
    settingsMenu->array_check_box[0]->setChecked(true);
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(settingsMenu->array_check_box[0] , SIGNAL(stateChanged(int)), settingsMenu, SLOT(on_checkBoxAutorun_stateChanged(int)), Qt::UniqueConnection));
}

void TestCSettingsMenu::testOn_checkBoxOfflineMode_stateChanged() {
    QApplication::setActiveWindow(settingsMenu);
    settingsMenu->array_check_box[1]->setFocus();
    QVERIFY(settingsMenu->array_check_box[1]->hasFocus());
    QSignalSpy spy(settingsMenu->array_check_box[1], &QCheckBox::stateChanged);
    QVERIFY(!settingsMenu->array_check_box[1]->isChecked());
    settingsMenu->array_check_box[1]->setChecked(true);
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(settingsMenu->array_check_box[1] , SIGNAL(stateChanged(int)), settingsMenu, SLOT(on_checkBoxOfflineMode_stateChanged(int)), Qt::UniqueConnection));
}

void TestCSettingsMenu::testSetText() {
    QApplication::setActiveWindow(settingsMenu);
    settingsMenu->lineEditTime->setFocus();
    QVERIFY(settingsMenu->lineEditTime->hasFocus());
    QSignalSpy spy(settingsMenu->saveButton, &QPushButton::clicked);
    settingsMenu->saveButton->click();
    QTest::keyClicks(settingsMenu->lineEditTime, "");
    QCOMPARE(settingsMenu->lineEditTime->text(), QString::number(REMINDER_TIME));
    settingsMenu->array_check_box[2]->setFocus();
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(settingsMenu->saveButton, SIGNAL(clicked()), settingsMenu, SLOT(setText()), Qt::UniqueConnection));
}

void TestCSettingsMenu::TimeOut()
{
    QWidgetList allToplevelWidgets = QApplication::topLevelWidgets();
    foreach (QWidget *w, allToplevelWidgets) {
        if (w->inherits("QMessageBox")) {
            QMessageBox *mb = qobject_cast<QMessageBox *>(w);
            QTest::keyClick(mb, Qt::Key_Enter);
        }
    }
}

void TestCSettingsMenu::testShowReminder() {
    QTimer::singleShot(500, this, SLOT(TimeOut()));
    settingsMenu->showReminder();
}

void TestCSettingsMenu::testOn_checkBoxReminder_stateChanged() {
    settingsMenu->array_check_box[2]->setFocus();
    QVERIFY(settingsMenu->array_check_box[2]->hasFocus());
    QSignalSpy spy(settingsMenu->array_check_box[2], &QCheckBox::stateChanged);
    QVERIFY(!settingsMenu->array_check_box[2]->isChecked());
    QVERIFY(!settingsMenu->lineEditTime->isEnabled());
    settingsMenu->array_check_box[2]->setChecked(true);
    QCOMPARE(spy.count(), 1);
    QVERIFY(!QObject::connect(settingsMenu->array_check_box[2] , SIGNAL(stateChanged(int)), settingsMenu, SLOT(on_checkBoxReminder_stateChanged(int)), Qt::UniqueConnection));
    QVERIFY(settingsMenu->lineEditTime->isEnabled());
}
