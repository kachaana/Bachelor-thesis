#ifndef TESTCLOGIN_H
#define TESTCLOGIN_H
#include <QTest>
#include <QtTest/QTest>
#include <QObject>
#include <QPointer>
#include <QSignalSpy>
#include "../../src/clogin.h"
#include "mock_chttpreceiver.h"

Q_DECLARE_METATYPE(CLogin)

class TestCLogin : public QObject
{
    Q_OBJECT
public:
    explicit TestCLogin(QObject *parent = nullptr);

public slots:
    void                    TimeOut();

private slots:
    void                     testShowLoginFail();
    void                     testAuthorizationSuccess();
    void                     testOn_ButtonLogIn_clicked();
    void                     testGUI();
};

#endif // TESTCLOGIN_H
