#include "mock_csettingsmenu.h"
#include "../bin/ui_csettingsmenu.h"

Mock_CSettingsMenu::Mock_CSettingsMenu() : _ui(new Ui::CSettingsMenu) {
    _ui->setupUi(this);
}

void Mock_CSettingsMenu::on_checkBoxAutorun_stateChanged(int) {}

void Mock_CSettingsMenu::on_checkBoxReminder_stateChanged(int) {}

void Mock_CSettingsMenu::setText() {}

void Mock_CSettingsMenu::showReminder() {}

void Mock_CSettingsMenu::on_checkBoxOfflineMode_stateChanged(int) {}
