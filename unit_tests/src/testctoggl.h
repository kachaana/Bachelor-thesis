#ifndef TESTCTOGGL_H
#define TESTCTOGGL_H
#include <QObject>
#include <QApplication>
#include <QTest>
#include <QtTest/QTest>
#include <QSpinBox>
#include <QSignalSpy>
#include "../../src/ctoggl.h"
#include "mock_cfilemanager.h"
#include "mock_csettingsmenu.h"
#include "mock_ctimeentrylist.h"

Q_DECLARE_METATYPE(CToggl)

class TestCToggl : public QObject
{
    Q_OBJECT
public:
    explicit TestCToggl(QObject *parent = nullptr);

private slots:
    void                    testSetUsername();
    void                    testOn_ButtonStart_clicked();
    void                    testOn_ButtonDes_clicked();
    void                    testOn_ButtonSettings_clicked();
    void                    testUpdateTable();
    void                    testCalculate();

private:
    CToggl                  *toggl;
    Mock_CTimeEntryList     *dummyEntryList;
};

#endif // TESTCTOGGL_H
