#include "ctoggl.h"
#include "ui_ctoggl.h"

CToggl::CToggl() : _ui(new Ui::CToggl) {
    _ui->setupUi(this);
    _timerTable = new QTimer(this);
    _fileManager = new CFileManager();
    _settingsMenu = new CSettingsMenu();
    _listEntries = new CTimeEntryList();
    userNameLabel = _ui->UserName;
    buttonStart = _ui->ButtonStart;
    buttonDes = _ui->ButtonDes;
    buttonSet = _ui->ButtonSettings;
    iconsAvailable = true;
    QObject::connect(_timerTable, SIGNAL(timeout()), this, SLOT(updateTable()));
    QObject::connect(_listEntries, SIGNAL(valueChanged()), this, SLOT(calculate()));
    _ui->verticalLayout->addWidget(_settingsMenu);
    _ui->verticalLayout->addWidget(_listEntries);
    _layoutItem = _ui->verticalLayout->itemAt(0);
    _layoutItem->widget()->setVisible(false);
    _ui->ButtonStart->setIcon(QIcon(_fileManager->getApplicationDirPath() + START_ICON));
    _ui->ButtonStart->setIconSize(QSize(SIZE_ICON, SIZE_ICON));
    _ui->ButtonDes->setIcon(QIcon(_fileManager->getApplicationDirPath() + DESTOP_ICON));
    _ui->ButtonDes->setIconSize(QSize(SIZE_ICON, SIZE_ICON));
    _ui->ButtonSettings->setIcon(QIcon(_fileManager->getApplicationDirPath() + SETTINGS_ICON));
    _ui->ButtonSettings->setIconSize(QSize(SIZE_ICON, SIZE_ICON));
}


CToggl::CToggl(const CToggl &) : IA_CToggl() {}

CToggl& CToggl::operator=(const CToggl &) {
    return *(new CToggl);
}

CToggl::~CToggl() {
    delete _ui;
    if(_fileManager) delete _fileManager;
}

/*!
 * \brief CToggl::setUsername Set user's name to main window.
 */

void CToggl::setUsername() {
    QString name = _fileManager->getNameFromFile();
    _ui->UserName->setText("Hello, " + name + "!");
}

/*!
 * \brief CToggl::on_ButtonDes_clicked Desktop's entries menu will be opened.
 */

void CToggl::on_ButtonDes_clicked() {
    _layoutItem = _ui->verticalLayout->itemAt(0);
    _layoutItem->widget()->setVisible(false);
    _layoutItem = _ui->verticalLayout->itemAt(1);
    _layoutItem->widget()->setVisible(true);
}

/*!
 * \brief CToggl::on_ButtonSettings_clicked Settings menu will be opened.
 */

void CToggl::on_ButtonSettings_clicked(){
    _layoutItem = _ui->verticalLayout->itemAt(0);
    _layoutItem->widget()->setVisible(true);
    _layoutItem = _ui->verticalLayout->itemAt(1);
    _layoutItem->widget()->setVisible(false);
}

/*!
 * \brief CToggl::_initiate_start Function call needed processes for starting time entry.
 */

void CToggl::_initiate_start() {
    _timerTable->start(TIMER_M_SEC);
    _listEntries->setIsStart(true);
    CTimeEntryItem * item = new CTimeEntryItem(_fileManager->getDesktopNameByNumber(_listEntries->getCurrentDesktop()), "true");
    _listEntries->setTimeEntryItem(item);
    if(!OFFLINE_MODE)
        _listEntries->server->sendRequest(_listEntries->getTimeEntryItem(), _listEntries->server->Action::START);
}

/*!
 * \brief CToggl::calculate Function was created for switching timer due to desktop changing. Any icon should be changed and
 *        any buttons pushed.
 */

void CToggl::calculate() {
    if(_listEntries->getIsStart()) {
            _timerTable->stop();
            _listEntries->setIsStart(false);
            _listEntries->server->sendRequest(_listEntries->getTimeEntryItem(), _listEntries->server->Action::STOP);
            _timerTable->start(TIMER_M_SEC);
            _fileManager->updateDesktopNames(_listEntries->tableModel->getList());
            _initiate_start();
            return;
        }
}

/*!
 * \brief CToggl::_setStartTimeIcons set icons as timer is stared.
 */

void CToggl::_setStartTimeIcons() {
    if(iconsAvailable) {
        _menuAction->setText(STOP_ACTION);
        _menuAction->setIcon(QIcon(_fileManager->getApplicationDirPath() + STOP_ICON));
        _iconStopStart->setIcon(QIcon(_fileManager->getApplicationDirPath() + TOGGL_ICON));
        _ui->ButtonStart->setIcon(QIcon(_fileManager->getApplicationDirPath() + STOP_ICON));
        _ui->ButtonStart->setIconSize(QSize(SIZE_ICON, SIZE_ICON));
    }
}

/*!
 * \brief CToggl::_setSopTimeIcons set icons as time is stopped.
 */

void CToggl::_setSopTimeIcons() {
    if(iconsAvailable) {
        _iconStopStart->setIcon(QIcon(_fileManager->getApplicationDirPath() + OFFLINE_ICON));
        _menuAction->setText(START_ACTION);
        _menuAction->setIcon(QIcon(_fileManager->getApplicationDirPath() + START_ICON));
        _ui->ButtonStart->setIcon(QIcon(_fileManager->getApplicationDirPath() + START_ICON));
        _ui->ButtonStart->setIconSize(QSize(SIZE_ICON, SIZE_ICON));
    }
}

/*!
 * \brief CToggl::on_ButtonStart_clicked Function will initiate all processes that shoul be triggered after button Start/Stop pushed.
 *        - changes of icons (red/green)
 *        - sending of time entries
 *        - updating of changes in ".conf" file
 *        - start/stop timer
 * \param action Can be BUTTONPUSHEd for manual stop/start. DESKTOPCHANGED behaves the same but doesn't change icons.
 */

void CToggl::on_ButtonStart_clicked() {
    if(!_listEntries->getIsStart()) {
          _setStartTimeIcons();
          _initiate_start();
     } else {
        _setSopTimeIcons();
        _timerTable->stop();
        _listEntries->setIsStart(false);
        if(!OFFLINE_MODE)
            _listEntries->server->sendRequest(_listEntries->getTimeEntryItem(), _listEntries->server->Action::STOP);
        _fileManager->updateDesktopNames(_listEntries->tableModel->getList());
     }
}

/*!
 * \brief generateTimeString Generation of the whole string to format "01:02" from input arguments.
 * \param hours Total hours.
 * \param minutes Total minutes.
 * \return String generated from hours, minutes integers.
 */

QString generateTimeString(int hours, int minutes) {
    QString ret;
    hours < 10 ? ret += "0" + QString::number(hours) : ret += QString::number(hours);
    ret += ":";
    minutes < 10 ? ret += "0" + QString::number(minutes) : ret += QString::number(minutes);
    return ret;
}

/*!
 * \brief CToggl::updateTable Function will call updates method from CTableModel with period equal to TIMER_M_SEC value.
 */

void CToggl::updateTable() {
     int cur = _listEntries->getCurrentDesktop();
     QPair <int, int> p;
     p.first = _listEntries->vectorTime.at(cur).first;
     p.second = _listEntries->vectorTime.at(cur).second + 1;
     if(p.second > 59) {
         p.first++;
         p.second = 0;
     }
     _listEntries->vectorTime.replace(cur,  p);
     QModelIndex index = _listEntries->tableModel->index(cur, 1, QModelIndex());
     _listEntries->tableModel->setData(index, generateTimeString(p.first, p.second), Qt::DisplayRole);
}

