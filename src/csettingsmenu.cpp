#include "csettingsmenu.h"
#include "ui_csettingsmenu.h"

#include <QMessageBox>


CSettingsMenu::CSettingsMenu() : _time_reminder(REMINDER_TIME), _ui(new Ui::CSettingsMenu) {
    _ui->setupUi(this);
    _file_manager = new CFileManager();
    _timer = new QTimer();
    array_check_box[0] = _ui->checkBoxAutorun;
    array_check_box[1] = _ui->checkBoxOfflineMode;
    array_check_box[2] = _ui->checkBoxReminder;
    lineEditTime = _ui->lineEditRemindeTime;
    saveButton = _ui->saveLineEditButton;
    _ui->lineEditRemindeTime->setEnabled(false);
    _ui->saveLineEditButton->setEnabled(false);
    _ui->saveLineEditButton->setFixedSize(QSize(50,25));
    connect(_ui->saveLineEditButton, SIGNAL(clicked()), this, SLOT(setText()));
    connect(_timer, SIGNAL(timeout()), this, SLOT(showReminder()));
    _updateSettings();
}


CSettingsMenu::CSettingsMenu(const CSettingsMenu &) : IA_CSettingsMenu() {}

CSettingsMenu& CSettingsMenu::operator=(const CSettingsMenu &) {
    array_check_box[0] = _ui->checkBoxAutorun;
    array_check_box[1] = _ui->checkBoxOfflineMode;
    array_check_box[2] = _ui->checkBoxReminder;
    connect(_ui->lineEditRemindeTime, SIGNAL(editingFinished()), this, SLOT(setText()));
    connect(_timer, SIGNAL(timeout()), this, SLOT(showReminder()));
    return *this;
}

CSettingsMenu::~CSettingsMenu(){
    delete _ui;
    if(_file_manager) delete _file_manager;
    if(_timer) delete _timer;
}

/*!
 * \brief CSettingsMenu::showReminder Shows Message box with reminder.
 */

void CSettingsMenu::showReminder() {
    QMessageBox reminder;
    reminder.setStandardButtons(QMessageBox::Ok);
    reminder.setText(REMINDER_MESSAGE);
    reminder.setWindowTitle(TITLE);
    int res = reminder.exec();
    if(res == QMessageBox::Ok)
        reminder.close();
}

/*!
 * \brief CSettingsMenu::on_checkBoxAutorun_stateChanged Function slot what is triggered after checkBoxAutorun status has changed.
 * \param arg1 Value means status of checkBox.
 */

void CSettingsMenu::on_checkBoxAutorun_stateChanged(int arg1){
    _file_manager->loadSettingChanges(0, arg1 == 0 ? 0 : 1);
    if(_ui->checkBoxAutorun->isChecked()) {
        _file_manager->createAutorunFile();
     } else {
        _file_manager->removeAutostartFile();
     }
}

/*!
 * \brief CSettingsMenu::_updateSettings Settings configuration will be loaded from ".confsettings" file (if are able) and will
 *        be updated in the application.
 */

void CSettingsMenu::_updateSettings() {
  vec_set vec = _file_manager->getSettings();
  if(vec.first){
      int counter = 0;
      for(auto v : vec.second) {
          if(counter == 1){
              OFFLINE_MODE = v;
          }
          if(counter == 2) {
               _ui->lineEditRemindeTime->setEnabled(v);
               _ui->saveLineEditButton->setEnabled(v);
          }
          if(counter == 3) {
              _time_reminder = v;
              if(_ui->lineEditRemindeTime->isEnabled())
                  _timer->start(_time_reminder * MILLISECONDS);
              break;
          }
         array_check_box[counter]->setChecked(v);
         counter++;
      }
        _ui->lineEditRemindeTime->setText(QString::number(_time_reminder));
  }
}

/*!
 * \brief CSettingsMenu::setText Setting the text in QLineEdit object.
 */

void CSettingsMenu::setText()  {
    QRegExp re("\\d*");
    QString input = _ui->lineEditRemindeTime->text();
    if (re.exactMatch(input) && input.toInt()){
        _time_reminder = input.toInt();
    } else {
        _time_reminder = REMINDER_TIME;
        _ui->lineEditRemindeTime->setText(QString::number(REMINDER_TIME));
    }
    _file_manager->loadSettingChanges(3, _time_reminder);
    _timer->start(_time_reminder * MILLISECONDS);
}

/*!
 * \brief CSettingsMenu::on_checkBoxReminder_stateChanged Function slot what is triggered after checkBoxReminder status has changed.
 * \param arg1 Value means status of checkBox.
 */

void CSettingsMenu::on_checkBoxReminder_stateChanged(int arg1) {
    _file_manager->loadSettingChanges(2, arg1 == 0 ? 0 : 1);
    if(arg1) {
        _ui->lineEditRemindeTime->setEnabled(true);
        _ui->saveLineEditButton->setEnabled(true);
        _timer->start(_time_reminder * MILLISECONDS);
    } else {
        _ui->lineEditRemindeTime->setEnabled(false);
        _ui->saveLineEditButton->setEnabled(false);
        _timer->stop();
    }
}

/*!
 * \brief CSettingsMenu::on_checkBoxOfflineMode_stateChanged Function slot what is triggered after checkBoxOfflineMode status has changed.
 * \param arg1 Value means status of checkBox.
 */

void CSettingsMenu::on_checkBoxOfflineMode_stateChanged(int arg1) {
    _file_manager->loadSettingChanges(1, (arg1 == 2) ? 1 : 0);
    if(arg1)
        OFFLINE_MODE = true;
    else {
        OFFLINE_MODE = false;
    }
}
