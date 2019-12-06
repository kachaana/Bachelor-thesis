#include "mock_cfilemanager.h"
#include <QDebug>

Mock_CFileManager::Mock_CFileManager() {}

void Mock_CFileManager::createConfFile() {}

void Mock_CFileManager::uploadTokenToFile(QByteArray) {}

bool Mock_CFileManager::getTokenFromFile(QString& token) {
    token = TEST_TOKEN;
    return RET_TRUE_FALSE;
}

bool Mock_CFileManager::tokenAvaliable() {
    return RET_TRUE_FALSE;
}

void Mock_CFileManager::saveNameToFile(QByteArray) {}

QString Mock_CFileManager::getNameFromFile() {
    return TEST_USER_NAME;
}

void Mock_CFileManager::updateDesktopNames(QList<QPair<QString, QString>>) {}

QString Mock_CFileManager::getDesktopNameByNumber(int) {
    return TEST_DESKTOP_NAME;
}

list_init Mock_CFileManager::loadEntriesFromFile() {
    QPair<bool,QList<QPair<QString, QString>>> ret_list;
    QList<QPair<QString, QString>> list;
    QPair<QString, QString> pair;
    pair.first = TEST_DESKTOP_NAME;
    pair.second = TEST_TIME;
    list.append(pair);
    ret_list.first = true;
    ret_list.second = list;
    return ret_list;
}

void Mock_CFileManager::createAutorunFile() {}

void Mock_CFileManager::checkAutorunDirExistance() {}

void Mock_CFileManager::removeAutostartFile() {}

void Mock_CFileManager::loadSettingChanges(int, int) {}

vec_set Mock_CFileManager::getSettings() {
    QPair<bool,QVector<int>> ret_pair;
    QVector<int>  vec = {1, 1, 1, 1};
    ret_pair.first = true;
    ret_pair.second = vec;
    return ret_pair;
}

void Mock_CFileManager::removeAllConfFiles() {}

void Mock_CFileManager::deleteLastDesktop(int) {}

