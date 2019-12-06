#ifndef IA_CSETTINGSMENU_H
#define IA_CSETTINGSMENU_H

#include <QWidget>

class IA_CSettingsMenu : public QWidget
{
    Q_OBJECT
public:
    explicit IA_CSettingsMenu(QWidget *parent = nullptr);

    virtual void                 on_checkBoxAutorun_stateChanged(int) = 0;
    virtual void                 on_checkBoxReminder_stateChanged(int) = 0;
    virtual void                 setText() = 0;
    virtual void                 showReminder() = 0;
    virtual void                 on_checkBoxOfflineMode_stateChanged(int) = 0;
};

#endif // IA_CSETTINGSMENU_H
