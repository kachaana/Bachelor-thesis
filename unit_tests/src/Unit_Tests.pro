#-------------------------------------------------
#
# Project created by QtCreator 2019-01-08T19:47:41
#
#-------------------------------------------------

QT       += core gui network x11extras testlib widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = unit_tests
#TEMPLATE = subdirs
CONFIG += link_pkgconfig testlib
PKGCONFIG += x11 glib-2.0
#SUBDIRS = gui logic
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS MOZ_X11
INCLUDEPATH += \

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES = \
    ../../src/ia_cwindowapplication.cpp \
    ../../src/ia_ctimeentryitem.cpp \
    ../../src/ia_chttpreceiver.cpp \
    ../../src/ia_clogin.cpp \
    ../../src/ia_ctablemodel.cpp \
    ../../src/ia_ctimeentrylist.cpp \
    ../../src/ia_csettingsmenu.cpp \
    ../../src/ia_csingleton.cpp \
    ../../src/ia_cfilemanager.cpp \
    ../../src/ia_ctoggl.cpp \
    ../../src/data.cpp \
    mock_cfilemanager.cpp \
    mock_chttpreceiver.cpp \
    mock_csettingsmenu.cpp \
    mock_ctablemodel.cpp \
    mock_ctimeentryitem.cpp \
    mock_ctimeentrylist.cpp \
    mock_ctoggl.cpp \
    test_data.cpp \
    testcfilemanager.cpp \
    testclogin.cpp \
    testcsettingsmenu.cpp \
    testctimeentryitem.cpp \
    testctoggl.cpp \
    testcwidnowapplication.cpp \
    ../../src/csingleton.cpp \
    ../../src/cfilemanager.cpp \
    ../../src/cwindowapplication.cpp \
    ../../src/ctimeentryitem.cpp \
    ../../src/chttpreceiver.cpp \
    ../../src/clogin.cpp \
    ../../src/ctablemodel.cpp \
    ../../src/ctimeentrylist.cpp \
    ../../src/csettingsmenu.cpp \
    ../../src/ctoggl.cpp \
    main.cpp \

HEADERS += \
    ../../src/ia_cwindowapplication.h \
    ../../src/ia_ctimeentryitem.h \
    ../../src/ia_chttpreceiver.h \
    ../../src/ia_clogin.h \
    ../../src/ia_ctablemodel.h \
    ../../src/ia_ctimeentrylist.h \
    ../../src/ia_csettingsmenu.h \
    ../../src/ia_csingleton.h \
    ../../src/ia_cfilemanager.h \
    ../../src/ia_ctoggl.h \
    ../../src/data.h \
    mock_cfilemanager.h \
    mock_chttpreceiver.h \
    mock_csettingsmenu.h \
    mock_ctablemodel.h \
    mock_ctimeentryitem.h \
    mock_ctoggl.h \
    test_data.h \
    testcfilemanager.h \
    ../../src/csingleton.h \
    ../../src/cfilemanager.h \
    ../../src/ctimeentryitem.h \
    ../../src/chttpreceiver.h \
    ../../bin/ui_clogin.h \
    ../../src/clogin.h \
    ../../src/ctablemodel.h \
    ../../bin/ui_ctimeentrylist.h \
    ../../src/ctimeentrylist.h \
    mock_ctimeentrylist.h \
    ../../bin/ui_csettingsmenu.h \
    ../../src/csettingsmenu.h \
    ../../bin/ui_ctoggl.h \
    ../../src/ctoggl.h \
    ../../bin/ui_cwindowapplication.h \
    ../../src/cwindowapplication.h \
    testclogin.h \
    testcsettingsmenu.h \
    testctimeentryitem.h \
    testctoggl.h \
    testcwidnowapplication.h

FORMS += \
    ../../src/csettingsmenu.ui \
    ../../src/ctoggl.ui \
    ../../src/ctimeentrylist.ui \
    ../../src/clogin.ui \
    ../../src/cwindowapplication.ui
