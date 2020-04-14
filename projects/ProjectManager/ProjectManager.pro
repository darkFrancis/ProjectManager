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

INCLUDEPATH += inc \
        inc/process \
        inc/settings \
        inc/tabs \
        inc/tabs/compiler\
        inc/tabs/git

SOURCES += \
        src/context.cpp \
        src/main.cpp \
        src/mainwindow.cpp \
        src/newproject.cpp \
        src/parser.cpp \
        src/process/processdisplayer.cpp \
        src/settings/logger.cpp \
        src/settings/settings.cpp \
        src/settings/settingswindow.cpp \
        src/tabs/compiler/compilerparamwindow.cpp \
        src/tabs/compiler/paramselectionwindow.cpp \
        src/tabs/compiler/sourceswindow.cpp \
        src/tabs/git/brancheswindow.cpp \
        src/tabs/git/conflictwindow.cpp \
        src/tabs/git/errorviewer.cpp \
        src/tabs/git/tagswindow.cpp \
        src/tabs/tabcompiler.cpp \
        src/tabs/tabdoxygen.cpp \
        src/tabs/tabgit.cpp \
        src/tabs/tabproject.cpp

HEADERS += \
        inc/context.hpp \
        inc/mainwindow.hpp \
        inc/newproject.hpp \
        inc/parser.hpp \
        inc/process/command.hpp \
        inc/process/processdisplayer.hpp \
        inc/settings/build.hpp \
        inc/settings/extern_doc.hpp \
        inc/settings/group_doc.hpp \
        inc/settings/logger.hpp \
        inc/settings/settings.hpp \
        inc/settings/settingswindow.hpp \
        inc/tabs/compiler/compilerparamwindow.hpp \
        inc/tabs/compiler/paramselectionwindow.hpp \
        inc/tabs/compiler/sourceswindow.hpp \
        inc/tabs/git/brancheswindow.hpp \
        inc/tabs/git/conflictwindow.hpp \
        inc/tabs/git/errorviewer.hpp \
        inc/tabs/git/tagswindow.hpp \
        inc/tabs/tab.hpp \
        inc/tabs/tabcompiler.hpp \
        inc/tabs/tabdoxygen.hpp \
        inc/tabs/tabgit.hpp \
        inc/tabs/tabproject.hpp

FORMS += \
        form/mainwindow.ui \
        form/newproject.ui \
        form/settings/settingswindow.ui \
        form/tabs/compiler/compilerparamwindow.ui \
        form/tabs/compiler/paramselectionwindow.ui \
        form/tabs/compiler/sourceswindow.ui \
        form/tabs/git/brancheswindow.ui \
        form/tabs/git/conflictwindow.ui \
        form/tabs/git/errorviewer.ui \
        form/tabs/git/tagswindow.ui \
        form/tabs/tabcompiler.ui \
        form/tabs/tabdoxygen.ui \
        form/tabs/tabgit.ui \
        form/tabs/tabproject.ui

RESOURCES += \
    ressources/darkstyle.qrc

QMAKE_POST_LINK += $$quote(cp -rn $$PWD/config $$DESTDIR/$$escape_expand(\n\t))
QMAKE_POST_LINK += $$quote(rm -f $$OUT_PWD/.qmake.stash$$escape_expand(\n\t))

QMAKE_CLEAN += $$DESTDIR/TARGET \
        $$OBJECTS_DIR/* \
        $$MOC_DIR/* \
        $$UI_DIR/* \
        $$OUT_PWD/.qmake.stash \
        $$MAKEFILE \
        $$DESTDIR/config/*
