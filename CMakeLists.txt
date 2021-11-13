cmake_minimum_required(VERSION 3.21.2)
project(ProjectManager VERSION 1.2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS
    form
    form/tabs
    form/tabs/git
    form/tabs/doxygen)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

file(GLOB_RECURSE FILES
    "src/*.cpp"
    "inc/*.hpp"
    "form/*.ui"
    "ressources/*.qrc")

add_executable(${PROJECT_NAME} ${FILES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} Logger Qt5::Core Qt5::Gui Qt5::Widgets)
if(NOT _DEFINED_VERSION)
    target_compile_definitions(${PROJECT_NAME} PUBLIC _DEFINED_VERSION="${PROJECT_VERSION}")
endif()
if(NOT _DEFINED_APPNAME)
    target_compile_definitions(${PROJECT_NAME} PUBLIC _DEFINED_APPNAME="${PROJECT}")
endif()
