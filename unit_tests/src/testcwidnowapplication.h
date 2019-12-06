#ifndef TESTCWIDNOWAPPLICATION_H
#define TESTCWIDNOWAPPLICATION_H
#include <QTest>
#include <QtTest/QTest>
#include <QObject>
#include <QSignalSpy>
#include <QWidget>
#include "../../src/cwindowapplication.h"
#include "mock_cfilemanager.h"
#include "mock_ctoggl.h"
#include "mock_chttpreceiver.h"
#include "../../src/data.h"
#include "../../bin/ui_cwindowapplication.h"
#include "../../src/clogin.h"


Q_DECLARE_METATYPE(CWindowApplication)

class TestCWidnowApplication : public QObject
{
    Q_OBJECT
public:
    explicit TestCWidnowApplication(QObject *parent = nullptr);

private slots:
    void                            testAuthorization();
    void                            testShowDialogWindow();
    void                            testGoToWeb();
    void                            testOpenApp();
    void                            testShowStartStopAction();
    void                            testLogOut();
    void                            testExit();

private:
    CWindowApplication             *windowApplication;
};

#endif // TESTCWIDNOWAPPLICATION_H
