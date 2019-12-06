#ifndef CSETTINGSMENU_H
#define CSETTINGSMENU_H
#include <QWidget>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QCheckBox>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>
#include "cfilemanager.h"
#include "ia_csettingsmenu.h"

namespace Ui {
    class CSettingsMenu;
}

class CSettingsMenu : public IA_CSettingsMenu {
    Q_OBJECT

public:
    CSettingsMenu();
    ~CSettingsMenu();
    CSettingsMenu(const CSettingsMenu &);
    CSettingsMenu& operator=(const CSettingsMenu &);

    void setFileManager( IA_CFileManager * newFileManager) {
        if(_file_manager) delete _file_manager;
        _file_manager = newFileManager;
    }

    QCheckBox           *array_check_box[CHECK_BOX_NUMBER];
    QLineEdit           *lineEditTime;
    QPushButton         *saveButton;

public slots:
    void                 on_checkBoxAutorun_stateChanged(int);
    void                 on_checkBoxReminder_stateChanged(int);
    void                 setText();
    void                 showReminder();
    void                 on_checkBoxOfflineMode_stateChanged(int);

private:
    void                 _updateSettings();
    int                  _time_reminder;
    Ui::CSettingsMenu   *_ui;
    IA_CFileManager     *_file_manager;
    QTimer              *_timer;
};

#endif // CSETTINGSMENU_H
