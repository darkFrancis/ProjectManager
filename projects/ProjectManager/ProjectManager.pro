QT       += core gui widgets

TARGET = ProjectManager
VERSION= 1.2.0
TEMPLATE = app
include(../includes/projects.pri)
include(../includes/Logger.pri)

SOURCES += \
        src/gui/tabs/TabDoxygen.cpp \
        src/gui/tabs/TabGit.cpp \
        src/gui/tabs/TabProject.cpp \
        src/gui/tabs/doxygen/DoxygenFilesHelper.cpp \
        src/gui/tabs/git/BranchesWindow.cpp \
        src/gui/tabs/git/ErrorViewer.cpp \
        src/gui/tabs/git/TagsWindow.cpp \
        src/main.cpp \
        src/gui/MainWindow.cpp \
        src/tools/Context.cpp \
        src/tools/InitParser.cpp

HEADERS += \
        inc/gui/MainWindow.hpp \
        inc/gui/tabs/Tab.hpp \
        inc/gui/tabs/TabDoxygen.hpp \
        inc/gui/tabs/TabGit.hpp \
        inc/gui/tabs/TabProject.hpp \
        inc/gui/tabs/doxygen/DoxygenFilesHelper.hpp \
        inc/gui/tabs/git/BranchesWindow.hpp \
        inc/gui/tabs/git/ErrorViewer.hpp \
        inc/gui/tabs/git/TagsWindow.hpp \
        inc/tools/Context.hpp \
        inc/tools/InitParser.hpp
        inc/version/version.hpp

FORMS += \
        form/MainWindow.ui \
        form/tabs/TabDoxygen.ui \
        form/tabs/TabGit.ui \
        form/tabs/TabProject.ui \
        form/tabs/doxygen/DoxygenFilesHelper.ui \
        form/tabs/git/BranchesWindow.ui \
        form/tabs/git/ErrorViewer.ui \
        form/tabs/git/TagsWindow.ui

INCLUDEPATH += \
        inc \
        inc/gui \
        inc/gui/tabs \
        inc/gui/tabs/git \
        inc/gui/tabs/doxygen \
        inc/tools \
        inc/version

RESOURCES += \
    ressources/darkstyle.qrc
