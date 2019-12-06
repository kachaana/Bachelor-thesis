#ifndef TESTCSETTINGSMENU_H
#define TESTCSETTINGSMENU_H
#include <QObject>
#include <QTest>
#include <QtTest/QTest>
#include <QSignalSpy>
#include <QMessageBox>
#include "../../src/csettingsmenu.h"
#include "../../src/data.h"
#include "mock_cfilemanager.h"
#include <QDebug>

Q_DECLARE_METATYPE(CSettingsMenu)

class TestCSettingsMenu : public QObject
{
    Q_OBJECT
public:
    explicit TestCSettingsMenu(QObject *parent = nullptr);

public slots:
    void                 TimeOut();

private slots:
    void                 testOn_checkBoxAutorun_stateChanged();
    void                 testOn_checkBoxReminder_stateChanged();
    void                 testSetText();
    void                 testShowReminder();
    void                 testOn_checkBoxOfflineMode_stateChanged();

private:
    CSettingsMenu       *settingsMenu;
};

#endif // TESTCSETTINGSMENU_H
