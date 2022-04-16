cmake_minimum_required(VERSION 3.5)

project(qt-custom-title-bar-demo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    PROJECT_SOURCES
    main.cpp main.qrc
    MainWidget.ui MainWidget.h MainWidget.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(qt-custom-title-bar-demo MANUAL_FINALIZATION ${PROJECT_SOURCES})
target_link_libraries(qt-custom-title-bar-demo PRIVATE Qt6::Widgets)

set_target_properties(
    qt-custom-title-bar-demo PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER qt-custom-title-bar-demo.ttc.icu
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

qt_finalize_executable(qt-custom-title-bar-demo)
