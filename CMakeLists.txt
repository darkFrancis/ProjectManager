cmake_minimum_required(VERSION 3.21.2)
project(ProjectManager VERSION 1.2.1)

execute_process(COMMAND conan install ${CMAKE_SOURCE_DIR})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_file(QtCmake common-qt.cmake)
include(${QtCmake})

set_ui_paths(
    form
    form/tabs
    form/tabs/git
    form/tabs/doxygen)

set_qt5_modules(Core Gui Widgets)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "inc/*.hpp"
    "form/*.ui"
    "ressources/*.qrc")

add_qt_bin(
    NAME ${PROJECT_NAME}
    SOURCES ${SOURCES}
    LIBS Logger
    INCLUDES inc)
set_common_defines()
