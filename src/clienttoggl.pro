#-------------------------------------------------
#
# Project created by QtCreator 2019-01-08T19:47:41
#
#-------------------------------------------------

QT       += core gui network x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = clienttoggl
#TEMPLATE = subdirs
CONFIG += link_pkgconfig
PKGCONFIG += x11 glib-2.0
#SUBDIRS = gui logic
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS MOZ_X11

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    chttpreceiver.cpp \
    ia_cfilemanager.cpp \
    ia_chttpreceiver.cpp \
    ia_clogin.cpp \
    ia_csettingsmenu.cpp \
    ia_csingleton.cpp \
    ia_ctablemodel.cpp \
    ia_ctimeentryitem.cpp \
    ia_ctimeentrylist.cpp \
    ia_ctoggl.cpp \
    ia_cwindowapplication.cpp \
        main.cpp \
    csingleton.cpp \
    cwindowapplication.cpp \
    clogin.cpp \
    ctoggl.cpp \
    csettingsmenu.cpp \
    ctimeentrylist.cpp \
    ctablemodel.cpp \
    ctimeentryitem.cpp \
    cfilemanager.cpp \
    data.cpp

HEADERS += \
    chttpreceiver.h \
    csingleton.h \
    cwindowapplication.h \
    clogin.h \
    ctoggl.h \
    csettingsmenu.h \
    ctimeentrylist.h \
    ctablemodel.h \
    ctimeentryitem.h \
    cfilemanager.h \
    data.h \
    ia_cfilemanager.h \
    ia_chttpreceiver.h \
    ia_clogin.h \
    ia_csettingsmenu.h \
    ia_csingleton.h \
    ia_ctablemodel.h \
    ia_ctimeentryitem.h \
    ia_ctimeentrylist.h \
    ia_ctoggl.h \
    ia_cwindowapplication.h

FORMS += \
    cwindowapplication.ui \
    clogin.ui \
    ctoggl.ui \
    csettingsmenu.ui \
    ctimeentrylist.ui



