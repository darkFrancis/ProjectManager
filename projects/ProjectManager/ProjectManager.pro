#-------------------------------------------------
#
# Project created by QtCreator 2019-12-21T13:29:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        context.cpp \
        main.cpp \
        mainwindow.cpp \
        newproject.cpp \
        parser.cpp \
        tabs/git/gitstatus.cpp \
        tabs/git/gitview.cpp \
        tabs/tabcompiler.cpp \
        tabs/tabdoxygen.cpp \
        tabs/tabgit.cpp

HEADERS += \
        context.hpp \
        mainwindow.hpp \
        newproject.hpp \
        parser.hpp \
        tabs/git/gitstatus.hpp \
        tabs/git/gitview.hpp \
        tabs/tabcompiler.hpp \
        tabs/tabdoxygen.hpp \
        tabs/tabgit.hpp

FORMS += \
        mainwindow.ui \
        newproject.ui \
        tabs/git/gitstatus.ui \
        tabs/tabcompiler.ui \
        tabs/tabdoxygen.ui \
        tabs/tabgit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
