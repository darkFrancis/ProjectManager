QT       += core gui widgets

TARGET = ProjectManager
TEMPLATE = app

CONFIG += c++17

CONFIG(debug, debug|release)
{
    DEFINES += _DEBUG
}

DESTDIR = build
MAKEFILE = $$DESTDIR/MakeFile
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
UI_DIR = $$DESTDIR/ui

INCLUDEPATH += process \
        settings \
        tabs \
        tabs/compiler\
        tabs/git

SOURCES += \
        context.cpp \
        main.cpp \
        mainwindow.cpp \
        newproject.cpp \
        parser.cpp \
        process/processdisplayer.cpp \
        settings/logger.cpp \
        settings/settings.cpp \
        settings/settingswindow.cpp \
        tabs/compiler/compilerparamwindow.cpp \
        tabs/compiler/paramselectionwindow.cpp \
        tabs/compiler/sourceswindow.cpp \
        tabs/git/brancheswindow.cpp \
        tabs/git/errorviewer.cpp \
        tabs/git/tagswindow.cpp \
        tabs/tabcompiler.cpp \
        tabs/tabdoxygen.cpp \
        tabs/tabgit.cpp \
        tabs/tabproject.cpp

HEADERS += \
        context.hpp \
        mainwindow.hpp \
        newproject.hpp \
        parser.hpp \
        process/command.hpp \
        process/processdisplayer.hpp \
        settings/build.hpp \
        settings/extern_doc.hpp \
        settings/group_doc.hpp \
        settings/logger.hpp \
        settings/settings.hpp \
        settings/settingswindow.hpp \
        tabs/compiler/compilerparamwindow.hpp \
        tabs/compiler/paramselectionwindow.hpp \
        tabs/compiler/sourceswindow.hpp \
        tabs/git/brancheswindow.hpp \
        tabs/git/errorviewer.hpp \
        tabs/git/tagswindow.hpp \
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
        tabs/git/brancheswindow.ui \
        tabs/git/errorviewer.ui \
        tabs/git/tagswindow.ui \
        tabs/tabcompiler.ui \
        tabs/tabdoxygen.ui \
        tabs/tabgit.ui \
        tabs/tabproject.ui

QMAKE_POST_LINK += $$quote(cp -rn $$PWD/config $$DESTDIR/$$escape_expand(\n\t))
QMAKE_POST_LINK += $$quote(rm -f $$OUT_PWD/.qmake.stash$$escape_expand(\n\t))

QMAKE_CLEAN += $$DESTDIR/TARGET \
        $$OBJECTS_DIR/* \
        $$MOC_DIR/* \
        $$UI_DIR/* \
        $$OUT_PWD/.qmake.stash \
        $$MAKEFILE \
        $$DESTDIR/config/*
