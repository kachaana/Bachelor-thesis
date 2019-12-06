#include "testcfilemanager.h"

TestCFileManager::TestCFileManager() {
    localDirPath = QCoreApplication::applicationDirPath();
    filemanager.setDirPath(localDirPath);
    byteArrayJSON1 = "{\"since\":1556650448,"
                     "\"data\":"
                              "{\"id\":2997759,"
                              "\"api_token\":\"";
    byteArrayJSON2 = "\","
                     "\"default_wid\":2159552,"
                     "\"email\":\"nastya.kachan.1996@gmail.com\","
                     "\"fullname\":\"";

    byteArrayJSON3 =  "\","
                      "\"created_at\":\"2017-07-14T11:18:23+00:00\","
                      "\"new_blog_post\":{"
                              "\"title\":\"How to Maximise Your Profits With Insights\","
                              "\"url\":\"https://blog.toggl.com/maximise-profits-insights/\","
                              "\"category\":\"time tracking\","
                              "\"pub_date\":\"2017-09-05T00:00:00Z\"},"
                      "\"should_upgrade\":true,"
                      "\"achievements_enabled\":true,"
                      "\"timezone\":\"Europe/Prague\","
                      "\"openid_enabled\":false,"
                      "\"workspaces\":[{\"id\":2159552,"
                      "\"name\":\"Nastya Kachan 1996's workspace\","
                      "\"api_token\":\"9620b169a51d447c1ae6539a3c568a4c\","
                      "\"at\":\"2018-09-01T08:21:37+00:00\",}}" ;

    testPair1.first = "ABCD";
    testPair1.second = "01:02";

    testPair2.first = "EFGT";
    testPair2.second = "04:33";

    autorunContent1 = "[Desktop Entry]\n"
                      "Type=Application\n"
                      "Exec=";
    autorunContent2 = "\n"
                      "Hidden=false\n"
                      "NoDisplay=false\n"
                      "X-GNOME-Autostart-enabled=true\n"
                      "Name[en_GB]=AutorunLinux\n"
                      "Name=AutorunLinux\n"
                      "Comment[en_GB]=AutorunLinux\n"
                      "Comment=AutorunLinux\n";

    setLine1 = 0;
    setLine2 = 0;
    setLine3 = 0;
    setLine4 = 0;
}

void TestCFileManager::testCreateConfFile() {
    filemanager.createConfFile();
    QFileInfo check_file(localDirPath + CONF);
    qDebug() << localDirPath + CONF;
    QVERIFY(check_file.exists());
    QCOMPARE(check_file.fileName(), ".conf");
    QFile file(localDirPath + CONF);
    QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
    QString log;
    log = file.readLine();
    QCOMPARE(log, DELIMETR + NEW_LINE);
    log = file.readLine();
    QCOMPARE(log, DELIMETR + NEW_LINE);
    log = file.readLine();
    QCOMPARE(log, DELIMETR + NEW_LINE);
    file.close();
}

void TestCFileManager::testUploadTokenToFile() {

    /* Case 1: .conf file is empty with user's data (only structure) */

    QFile file(localDirPath + CONF);
    qint64 fileSizeBefore = file.size();
    QString fakeToken = "18c5b446ec620f9104b317cef0ca1e45";
    QByteArray byteArray = byteArrayJSON1 + fakeToken.toUtf8() + byteArrayJSON2 + DEFAULT_USER_NAME.toUtf8() + byteArrayJSON3;
    filemanager.uploadTokenToFile(byteArray);
    QCOMPARE(file.size(), fileSizeBefore + fakeToken.length());
    QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream stream(&file);
    QString log;
    log = file.readLine();
    QCOMPARE(log, DELIMETR + fakeToken + "\n");
    fileSizeBefore = file.size();

     /* Case 2: .conf contains token and empty array was sent to the function */

    byteArray = "";
    filemanager.uploadTokenToFile(byteArray);
    QCOMPARE(fileSizeBefore, file.size());
    file.close();
}

void TestCFileManager::testGetTokenFromFile() {

    /* Case 1: .conf file doesn't exist */

    QFile file(localDirPath + CONF);
    file.remove();
    QString tokenTest;

    QVERIFY2(!filemanager.getTokenFromFile(tokenTest), "Case 1");
    QCOMPARE(tokenTest, "");

    /* Case 2: .conf exists, but any token stored there. */

    QFile file2(localDirPath + CONF);
    QVERIFY(!filemanager.getTokenFromFile(tokenTest));
    QCOMPARE(tokenTest, "");
    file2.close();

    /* Case 3: positive scenario */

    QString tokenToStore = "18c5b446ec620f9104b317cef0ca1e45";
    QVERIFY(file.open(QIODevice::ReadWrite));
    QTextStream stream( &file );
    stream << DELIMETR << tokenToStore << endl;
    stream << DELIMETR << endl;
    stream << DELIMETR << endl;
    QVERIFY(filemanager.getTokenFromFile(tokenTest));
    QCOMPARE(tokenTest, tokenToStore);
    file.close();
}

void TestCFileManager::testSaveNameToFile() {

    /* Case 1: .conf file doesn't exist */

    QFile file(localDirPath + CONF);
    file.remove();
    QByteArray nameTest = "Test Test";
    QFileInfo check_file(localDirPath + CONF);
    QVERIFY(!check_file.exists());
    QFile file2(localDirPath + CONF);
    filemanager.createConfFile();
    filemanager.saveNameToFile(nameTest);
    QVERIFY(file2.open(QIODevice::ReadOnly));
    QString line;
    line = file2.readLine();
    line = file2.readLine();
    QCOMPARE(line, DELIMETR + nameTest + NEW_LINE);
    file2.close();

    /* Case 2: positive scenario */

    file2.remove();
    filemanager.createConfFile();
    filemanager.saveNameToFile(nameTest);
    QVERIFY(file.open(QIODevice::ReadWrite));
    line = file.readLine();
    line = file.readLine();
    QCOMPARE(line, DELIMETR + nameTest + NEW_LINE);
    file.close();
}

void TestCFileManager::testGetNameFromFile() {

   /* Case 1: ".conf" file doesn't exist. */

    QFile file(localDirPath + CONF);
    file.remove();
    filemanager.createConfFile();
    QString testName = filemanager.getNameFromFile();
    QCOMPARE(testName, DEFAULT_USER_NAME);
    file.close();

    /* Case 2: no token in a file. */

    QByteArray nameToCompare = "Test Name";
    filemanager.saveNameToFile(nameToCompare);
    testName = filemanager.getNameFromFile();
    QCOMPARE(testName, DEFAULT_USER_NAME);

    /* Case 3: positive scenario. */

    QString fakeToken = "18c5b446ec620f9104b317cef0ca1e45";
    QByteArray byteArray = byteArrayJSON1 + fakeToken.toUtf8() + byteArrayJSON2 + nameToCompare + byteArrayJSON3;
    filemanager.uploadTokenToFile(byteArray);
    testName = filemanager.getNameFromFile();
    QCOMPARE(testName, nameToCompare);
}

void TestCFileManager::testUpdateDesktopNames() {
   QList<QPair<QString, QString>>   testList;

   testList.push_back(testPair1);
   testList.push_back(testPair2);

   QFile file(localDirPath + CONF);
   file.remove();
   filemanager.createConfFile();
   filemanager.updateDesktopNames(testList);

   file.open(QIODevice::ReadOnly | QIODevice::Text);
   if(file.isOpen()) {
       QTextStream org(&file);
       QString testLine;
       testLine = org.readLine();
       testLine = org.readLine();
       testLine = org.readLine();
       testLine = org.readLine();
       QCOMPARE(testPair1.first + DELIMETR + testPair1.second, testLine);
       testLine = org.readLine();
       QCOMPARE(testPair2.first + DELIMETR + testPair2.second, testLine);
   }
   file.close();
}

void TestCFileManager::testGetDesktopNameByNumber() {
    QString testDesktopName;
    testDesktopName = filemanager.getDesktopNameByNumber(0);
    QCOMPARE(testDesktopName, testPair1.first);
    testDesktopName = filemanager.getDesktopNameByNumber(1);
    QCOMPARE(testDesktopName, testPair2.first);
}

void TestCFileManager::testLoadEntriesFromFile() {
    list_init retTestValue = filemanager.loadEntriesFromFile();
    QVERIFY(retTestValue.first);
    QCOMPARE(retTestValue.second.at(0).first, testPair1.first);
    QCOMPARE(retTestValue.second.at(0).second, testPair1.second);
    QCOMPARE(retTestValue.second.at(1).first, testPair2.first);
    QCOMPARE(retTestValue.second.at(1).second, testPair2.second);

    QFile file(localDirPath + CONF);
    file.remove();

    retTestValue = filemanager.loadEntriesFromFile();
    QVERIFY(!retTestValue.first);
    QCOMPARE(retTestValue.second.size(), 0);
}

void TestCFileManager::testCreateAutorunFile() {
    QString appPath = filemanager.getApplicationDirPath() + "/unit_tests";
    QString testAutorunContent = autorunContent1 + appPath + autorunContent2;
    QFile autorunRemove(filemanager.getAutostartFilePath());
    autorunRemove.remove();
    QFileInfo check_file(filemanager.getAutostartFilePath());
    QVERIFY(!check_file.exists());
    filemanager.createAutorunFile();
    QFile fileAutorun(filemanager.getAutostartFilePath());
    QVERIFY(fileAutorun.exists());
    QVERIFY(fileAutorun.open(QIODevice::ReadOnly | QIODevice::Text));
    QByteArray testContent = fileAutorun.read(fileAutorun.size());
    QCOMPARE(testContent, testAutorunContent.toUtf8());
    fileAutorun.close();
}

void TestCFileManager::testRemoveAutostartFile() {
    QFileInfo check_file(filemanager.getAutostartFilePath());
    QVERIFY(check_file.exists());
    filemanager.removeAutostartFile();
    QFileInfo check_file2(filemanager.getAutostartFilePath());
    QVERIFY(!check_file2.exists());
}

void TestCFileManager::testLoadSettingChanges() {
    QFile setconfFile(filemanager.getApplicationDirPath() + SETTINGS);
    setconfFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(&setconfFile);

    stream << QString::number(setLine1) << endl;
    stream << QString::number(setLine2) << endl;
    stream << QString::number(setLine3) << endl;
    stream << QString::number(setLine4) << endl;
    setconfFile.close();

    setLine2 = 1;
    filemanager.loadSettingChanges(1, 1);
    setconfFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString testLine;
    testLine = setconfFile.readLine();
    QCOMPARE(testLine, QString::number(setLine1) + "\n");
    testLine = setconfFile.readLine();
    QCOMPARE(testLine, QString::number(setLine2) + "\n");
    testLine = setconfFile.readLine();
    QCOMPARE(testLine, QString::number(setLine3) + "\n");
    testLine = setconfFile.readLine();
    QCOMPARE(testLine, QString::number(setLine4) + "\n");
    setconfFile.close();
}

void TestCFileManager::testGetSettings() {
    vec_set testRetValue;
    testRetValue = filemanager.getSettings();
    QVERIFY(testRetValue.first);
    QCOMPARE(testRetValue.second.at(0), setLine1);
    QCOMPARE(testRetValue.second.at(1), setLine2);
    QCOMPARE(testRetValue.second.at(2), setLine3);
    QCOMPARE(testRetValue.second.at(3), setLine4);
    QFile fileSet(filemanager.getApplicationDirPath() + SETTINGS);
    fileSet.remove();
    QFileInfo fileToCheck(filemanager.getApplicationDirPath() + SETTINGS);
    QVERIFY(!fileToCheck.exists());
    testRetValue = filemanager.getSettings();
    QVERIFY(!testRetValue.first);
    QCOMPARE(testRetValue.second.size(), 0);
}

void TestCFileManager::testDeleteLastDesktop() {
    QList<QPair<QString, QString>>   testList;

    testList.push_back(testPair1);
    testList.push_back(testPair2);

    filemanager.updateDesktopNames(testList);
    list_init retTestValue = filemanager.loadEntriesFromFile();
    QCOMPARE(retTestValue.second.size(), 2);
    filemanager.deleteLastDesktop(1);
    retTestValue = filemanager.loadEntriesFromFile();
    QVERIFY(retTestValue.first);
    QCOMPARE(retTestValue.second.size(), 1);
    QCOMPARE(retTestValue.second.at(0).first, testPair1.first);
    QCOMPARE(retTestValue.second.at(0).second, testPair1.second);
}

void TestCFileManager::testRemoveAllConfFiles() {
    QFileInfo confTest(filemanager.getConfPath());
    QFileInfo setTest(filemanager.getApplicationDirPath() + SETTINGS);
    filemanager.createAutorunFile();
    QFileInfo autorunTest(filemanager.getAutostartFilePath());
    QVERIFY(confTest.exists());
    QVERIFY(setTest.exists());
    QVERIFY(autorunTest.exists());
    filemanager.removeAllConfFiles();
    QFileInfo confTest2(filemanager.getConfPath());
    QFileInfo setTest2(filemanager.getApplicationDirPath() + SETTINGS);
    QFileInfo autotunTest2(filemanager.getAutostartFilePath());
    QVERIFY(!confTest2.exists());
    QVERIFY(!setTest2.exists());
    QVERIFY(!autotunTest2.exists());
}
//#include "testcfilemanager.moc"
