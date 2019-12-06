#ifndef CFILEMANAGER_H
#define CFILEMANAGER_H
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>
#include "ia_cfilemanager.h"

class CFileManager : public IA_CFileManager {

public:
    CFileManager();
    ~CFileManager();

    void                    createConfFile();
    void                    uploadTokenToFile(QByteArray);
    bool                    getTokenFromFile(QString& token);
    bool                    tokenAvaliable();
    void                    saveNameToFile(QByteArray);
    QString                 getNameFromFile();
    void                    updateDesktopNames(QList<QPair<QString, QString>>);
    QString                 getDesktopNameByNumber(int);
    list_init               loadEntriesFromFile();
    void                    createAutorunFile();
    void                    checkAutorunDirExistance();
    void                    removeAutostartFile();
    void                    loadSettingChanges(int, int);
    vec_set                 getSettings();
    void                    removeAllConfFiles();
    void                    deleteLastDesktop(int);

private:
    QPair<QString,QString>  _parseTimeString(QString);
    QString                 _getDesktopName(QString);
};

#endif // CFILEMANAGER_H
