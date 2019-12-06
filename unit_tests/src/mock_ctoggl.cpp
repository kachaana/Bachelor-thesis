#include "mock_ctoggl.h"

Mock_CToggl::Mock_CToggl() {}

void Mock_CToggl::setUsername() {}

void Mock_CToggl::setIconStopStart(QSystemTrayIcon *) {}

void Mock_CToggl::setAction(QAction *) {}

bool Mock_CToggl::getIsStart() const {
    return RET_TRUE_FALSE;
}

void Mock_CToggl::on_ButtonStart_clicked() {}

void Mock_CToggl::on_ButtonDes_clicked() {}

void Mock_CToggl::on_ButtonSettings_clicked() {}

void Mock_CToggl::updateTable() {}

void Mock_CToggl::calculate() {}

