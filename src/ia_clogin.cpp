#include "ia_clogin.h"

IA_CLogin::IA_CLogin(QWidget *parent) : QWidget(parent) {}

IA_CLogin::~IA_CLogin() {
    if(_server) delete _server;
}
