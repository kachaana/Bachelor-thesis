#ifndef TESTCFILEMANAGER_H
#define TESTCFILEMANAGER_H
#include <QTest>
#include "../../src/cfilemanager.h"
#include "../../src/data.h"

Q_DECLARE_METATYPE(CFileManager)

class TestCFileManager: public QObject {
    Q_OBJECT
public:
    TestCFileManager();
private slots:
    void                    testCreateConfFile();
    void                    testUploadTokenToFile();
    void                    testGetTokenFromFile();
    void                    testSaveNameToFile();
    void                    testGetNameFromFile();
    void                    testUpdateDesktopNames();
    void                    testGetDesktopNameByNumber();
    void                    testLoadEntriesFromFile();
    void                    testCreateAutorunFile();
    void                    testRemoveAutostartFile();
    void                    testLoadSettingChanges();
    void                    testGetSettings();
    void                    testDeleteLastDesktop();
    void                    testRemoveAllConfFiles();

private:
    CFileManager            filemanager;
    QString                 localDirPath;
    QByteArray              byteArrayJSON1;
    QByteArray              byteArrayJSON2;
    QByteArray              byteArrayJSON3;
    QPair<QString,QString>  testPair1;
    QPair<QString,QString>  testPair2;
    QString                 autorunContent1;
    QString                 autorunContent2;
    int                     setLine1;
    int                     setLine2;
    int                     setLine3;
    int                     setLine4;
};

#endif // TESTCFILEMANAGER_H
