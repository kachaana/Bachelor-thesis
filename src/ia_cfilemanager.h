#ifndef IA_CFILEMANAGER_H
#define IA_CFILEMANAGER_H
#include <QByteArray>
#include <QString>
#include <QList>
#include <QPair>
#include "data.h"

typedef  QPair<bool,QList<QPair<QString, QString>>>     list_init;
typedef  QPair<bool,QVector<int>>                       vec_set;

class IA_CFileManager {
public:
    virtual
    ~IA_CFileManager();

    virtual void                    createConfFile() = 0;
    virtual bool                    getTokenFromFile(QString& token) = 0;
    virtual void                    updateDesktopNames(QList<QPair<QString, QString>>) = 0;
    virtual void                    uploadTokenToFile(QByteArray) = 0;
    virtual QString                 getDesktopNameByNumber(int) = 0;
    virtual list_init               loadEntriesFromFile() = 0;
    virtual void                    createAutorunFile() = 0;
    virtual void                    checkAutorunDirExistance() = 0;
    virtual void                    removeAutostartFile() = 0;
    virtual vec_set                 getSettings() = 0;
    virtual void                    loadSettingChanges(int, int) = 0;
    virtual void                    removeAllConfFiles() = 0;
    virtual bool                    tokenAvaliable() = 0;
    virtual void                    saveNameToFile(QByteArray) = 0;
    virtual QString                 getNameFromFile() = 0;
    virtual void                    deleteLastDesktop(int) = 0;

    void setDirPath(QString newPath) {
        _appDirPath = newPath;
    }

    const QString           getConfPath() {
        return _appDirPath + CONF;
    }

    const QString           getAutostartFilePath() {
        return _autostartPath + DESKTOP;
    }
    const QString           getApplicationDirPath() {
        return _appDirPath;
    }

protected:
    QString                 _appDirPath;
    QString                 _autostartPath;
    QString                 _appPath;
};

#endif // IA_CFILEMANAGER_H
