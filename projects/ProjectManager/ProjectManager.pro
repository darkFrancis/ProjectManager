QT       += core gui widgets

TARGET = ProjectManager
VERSION= 1.0
TEMPLATE = app

CONFIG += c++17

DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\" \
        APP_NAME=\"\\\"$${TARGET}\\\"\"

CONFIG(debug, release | debug):DEFINES+=_DEBUG

SOURCES += \
        src/gui/tabs/TabDoxygen.cpp \
        src/gui/tabs/TabGit.cpp \
        src/gui/tabs/TabProject.cpp \
        src/gui/tabs/git/BranchesWindow.cpp \
        src/gui/tabs/git/ErrorViewer.cpp \
        src/gui/tabs/git/TagsWindow.cpp \
        src/main.cpp \
        src/gui/MainWindow.cpp \
        src/tools/Context.cpp \
        src/tools/InitParser.cpp \
        src/tools/Logger.cpp

HEADERS += \
        inc/gui/MainWindow.hpp \
        inc/gui/tabs/Tab.hpp \
        inc/gui/tabs/TabDoxygen.hpp \
        inc/gui/tabs/TabGit.hpp \
        inc/gui/tabs/TabProject.hpp \
        inc/gui/tabs/git/BranchesWindow.hpp \
        inc/gui/tabs/git/ErrorViewer.hpp \
        inc/gui/tabs/git/TagsWindow.hpp \
        inc/tools/Context.hpp \
        inc/tools/InitParser.hpp \
        inc/tools/Logger.hpp \
        inc/version.hpp

FORMS += \
        form/MainWindow.ui \
        form/tabs/TabDoxygen.ui \
        form/tabs/TabGit.ui \
        form/tabs/TabProject.ui \
        form/tabs/git/BranchesWindow.ui \
        form/tabs/git/ErrorViewer.ui \
        form/tabs/git/TagsWindow.ui

INCLUDEPATH += \
        inc \
        inc/gui \
        inc/gui/tabs \
        inc/gui/tabs/git \
        inc/tools

RESOURCES += \
    ressources/darkstyle.qrc
