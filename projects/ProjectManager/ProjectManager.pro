QT       += core gui widgets

TARGET = ProjectManager
VERSION=0.1
TEMPLATE = app

CONFIG += c++17

DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\" \
        APP_NAME=\"\\\"$${TARGET}\\\"\"

CONFIG(debug, release | debug):DEFINES+=_DEBUG

SOURCES += \
        src/gui/tabs/git/brancheswindow.cpp \
        src/gui/tabs/git/errorviewer.cpp \
        src/gui/tabs/git/tagswindow.cpp \
        src/gui/tabs/tabdoxygen.cpp \
        src/gui/tabs/tabgit.cpp \
        src/main.cpp \
        src/gui/MainWindow.cpp \
        src/tools/Logger.cpp

HEADERS += \
        inc/gui/MainWindow.hpp \
        inc/gui/tabs/git/brancheswindow.hpp \
        inc/gui/tabs/git/errorviewer.hpp \
        inc/gui/tabs/git/tagswindow.hpp \
        inc/gui/tabs/tabdoxygen.hpp \
        inc/gui/tabs/tabgit.hpp \
        inc/tools/Logger.hpp \
        inc/version.hpp

FORMS += \
        form/MainWindow.ui \
        form/tabs/git/brancheswindow.ui \
        form/tabs/git/errorviewer.ui \
        form/tabs/git/tagswindow.ui \
        form/tabs/tabdoxygen.ui \
        form/tabs/tabgit.ui

INCLUDEPATH += \
        inc \
        inc/gui \
        inc/tools

RESOURCES += \
    ressources/darkstyle.qrc
