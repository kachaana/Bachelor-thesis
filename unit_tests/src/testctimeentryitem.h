#ifndef TESTCTIMEENTRYITEM_H
#define TESTCTIMEENTRYITEM_H
#include <QTest>
#include <QtTest/QTest>
#include "../../src/ctimeentryitem.h"

Q_DECLARE_METATYPE(CTimeEntryItem)

class TestCTimeEntryItem : public QObject
{
    Q_OBJECT
public:
    explicit TestCTimeEntryItem(QObject *parent = nullptr);

private slots:
    void                testTimeEntryToJSON();
    void                testGetTimeEntryIDFromResponse();
};

#endif // TESTCTIMEENTRYITEM_H
