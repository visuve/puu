cmake_minimum_required(VERSION 3.16)

project(puu LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

file(GLOB puu_sources "*.cpp" "*.hpp" "*.ui")

add_executable(puu ${puu_sources})

target_link_libraries(puu PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
