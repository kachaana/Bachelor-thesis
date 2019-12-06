#ifndef MOCK_CSETTINGS_H
#define MOCK_CSETTINGS_H
#include "../../src/ia_csettingsmenu.h"
#include "../../src/csettingsmenu.h"

namespace Ui {
    class CSettingsMenu;
}

class Mock_CSettingsMenu : public IA_CSettingsMenu {
public:
    Mock_CSettingsMenu();

public slots:
    void                 on_checkBoxAutorun_stateChanged(int);
    void                 on_checkBoxReminder_stateChanged(int);
    void                 setText();
    void                 showReminder();
    void                 on_checkBoxOfflineMode_stateChanged(int);

private:
    Ui::CSettingsMenu   *_ui;
};

#endif // MOCK_CSETTINGS_H
