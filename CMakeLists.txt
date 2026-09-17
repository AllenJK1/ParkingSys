cmake_minimum_required(VERSION 3.16)
project(ParkingSys LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    include/structures.hpp
    ui/mainwindow.ui
    ui/CustomerInfo.ui
    ui/ReserveParking.ui
)

add_executable(ParkingSys ${PROJECT_SOURCES})

target_include_directories(ParkingSys PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ParkingSys PRIVATE Qt6::Widgets)

if(WIN32)
    set_target_properties(ParkingSys PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
