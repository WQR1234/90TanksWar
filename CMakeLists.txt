cmake_minimum_required(VERSION 3.23)
project(90TanksWar)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "E:\\Qt\\Qt5.12.12\\5.12.12\\mingw73_64")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include_directories(./)
include_directories(./gameObjectClasses)
include_directories(./gameManagerClasses)

aux_source_directory(./ SRC_LIST)
aux_source_directory(./gameObjectClasses GO_LIST)
aux_source_directory(./gameManagerClasses GM_LIST)

add_executable(90TanksWar main.cpp ${SRC_LIST} ${GO_LIST} ${GM_LIST} startWidget.ui chooseScene.ui gameWidget.ui res.qrc)
target_link_libraries(90TanksWar
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )


