#ifndef MOCK_CFILEMANAGER_H
#define MOCK_CFILEMANAGER_H
#include "../../src/ia_cfilemanager.h"
#include "test_data.h"

class Mock_CFileManager : public IA_CFileManager {
public:
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

public:
    Mock_CFileManager();
};

#endif // MOCK_CFILEMANAGER_H
