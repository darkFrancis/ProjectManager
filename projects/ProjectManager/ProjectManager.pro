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
        settings/logger.cpp \
        settings/settings.cpp \
        settings/settingswindow.cpp \
        tabs/compiler/compilerparamwindow.cpp \
        tabs/compiler/paramselectionwindow.cpp \
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
        settings/build.hpp \
        settings/extern_doc.hpp \
        settings/group_doc.hpp \
        settings/logger.hpp \
        settings/settings.hpp \
        settings/settingswindow.hpp \
        tabs/compiler/compilerparamwindow.hpp \
        tabs/compiler/paramselectionwindow.hpp \
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
        tabs/compiler/compilerparamwindow.ui \
        tabs/compiler/paramselectionwindow.ui \
        tabs/compiler/sourceswindow.ui \
        tabs/tabcompiler.ui \
        tabs/tabdoxygen.ui \
        tabs/tabgit.ui \
        tabs/tabproject.ui

QMAKE_CLEAN += $$OUT_PWD/build/*
QMAKE_POST_LINK += $$quote(cp -rn $$PWD/config $$OUT_PWD/$$escape_expand(\n\t))
