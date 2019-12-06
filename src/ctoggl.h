#ifndef CTOGGL_H
#define CTOGGL_H
#include <QVBoxLayout>
#include <QAction>
#include <QSystemTrayIcon>
#include <QLabel>
#include <QPushButton>
#include "csettingsmenu.h"
#include "ctimeentrylist.h"
#include "ia_ctoggl.h"
#include "ui_ctoggl.h"

namespace Ui {
    class CToggl;
}

class CToggl : public IA_CToggl {
    Q_OBJECT

public:
    CToggl();
    ~CToggl();
    CToggl(const CToggl &);
    CToggl& operator=(const CToggl &);

    void setIconStopStart(QSystemTrayIcon * icon) {
        _iconStopStart = icon;
    }

    void setAction(QAction * action) {
        _menuAction = action;
    }

    bool getIsStart() const {
        return _listEntries->getIsStart();
    }

    void setSettingsMenu(IA_CSettingsMenu * sMenu) {
       if(_settingsMenu) delete _settingsMenu;
        _settingsMenu = sMenu;
        _ui->verticalLayout->addWidget(_settingsMenu);
    }

    void setTimeEntryList(IA_CTimeEntryList * list) {
       if(_listEntries) delete _listEntries;
        _listEntries = list;
        _ui->verticalLayout->addWidget(_listEntries);
        QObject::connect(_listEntries, SIGNAL(valueChanged()), this, SLOT(calculate()));
    }

    void setFileManager(IA_CFileManager * fileManager) {
        if (_fileManager) delete _fileManager;
        _fileManager = fileManager;
    }

    QTimer *getTimerTable() const {
        return _timerTable;
    }

    IA_CTimeEntryList *getTimeEntryList() const {
        return _listEntries;
    }

    void                    setUsername();

    QLabel                 *userNameLabel;
    QPushButton            *buttonStart;
    QPushButton            *buttonDes;
    QPushButton            *buttonSet;
    bool                    iconsAvailable;

signals:
    void                    valueChanged();

public slots:
    void                    on_ButtonStart_clicked();
    void                    on_ButtonDes_clicked();
    void                    on_ButtonSettings_clicked();
    void                    updateTable();
    void                    calculate();

private:
    Ui::CToggl             *_ui;
    void                    _setStartTimeIcons();
    void                    _setSopTimeIcons();
    void                    _initiate_start();
    QSystemTrayIcon        *_iconStopStart;
    IA_CSettingsMenu       *_settingsMenu;
    QLayoutItem            *_layoutItem;
    IA_CTimeEntryList      *_listEntries;
    QTimer                 *_timerTable;
    QAction                *_menuAction;
    IA_CFileManager        *_fileManager;
};
#endif // CTOGGL_H
