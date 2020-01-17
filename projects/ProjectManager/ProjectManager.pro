QT       += core gui widgets

TARGET = ProjectManager
TEMPLATE = app

CONFIG += c++17

CONFIG(debug, debug|release)
{
    DEFINES += _DEBUG
}

SOURCES += \
        context.cpp \
        main.cpp \
        mainwindow.cpp \
        newproject.cpp \
        parser.cpp \
        settings/settings.cpp \
        settings/settingswindow.cpp \
        tabs/compiler/sourceswindow.cpp \
        tabs/tabcompiler.cpp \
        tabs/tabdoxygen.cpp \
        tabs/tabgit.cpp \
        tabs/tabproject.cpp

HEADERS += \
        context.hpp \
        mainwindow.hpp \
        newproject.hpp \
        parser.hpp \
        settings/settings.hpp \
        settings/settingswindow.hpp \
        tabs/compiler/sourceswindow.hpp \
        tabs/tab.hpp \
        tabs/tabcompiler.hpp \
        tabs/tabdoxygen.hpp \
        tabs/tabgit.hpp \
        tabs/tabproject.hpp

FORMS += \
        mainwindow.ui \
        newproject.ui \
        settings/settingswindow.ui \
        tabs/compiler/sourceswindow.ui \
        tabs/tabcompiler.ui \
        tabs/tabdoxygen.ui \
        tabs/tabgit.ui \
        tabs/tabproject.ui

QMAKE_CLEAN += $$OUT_PWD/build/*
QMAKE_POST_LINK += $$quote(cp -r $$PWD/config $$OUT_PWD/$$escape_expand(\n\t))
