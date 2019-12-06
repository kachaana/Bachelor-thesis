#include <QTest>
#include "testcfilemanager.h"
#include "testctimeentryitem.h"
#include "testclogin.h"
#include "testctoggl.h"
#include "testcwidnowapplication.h"
#include "testcsettingsmenu.h"
#include "../../src/csingleton.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QTest::qExec(new TestCFileManager, argc, argv);
    QTest::qExec(new TestCTimeEntryItem, argc, argv);
    QTest::qExec(new TestCLogin, argc, argv);
    QTest::qExec(new TestCToggl, argc, argv);
    QTest::qExec(new TestCWidnowApplication, argc, argv);
    QTest::qExec(new TestCSettingsMenu, argc, argv);
    return 0;
}
