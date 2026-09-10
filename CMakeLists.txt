cmake_minimum_required(VERSION 3.16)
project(ParkingSy LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#Enabling QT code gens
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets)
add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE Qt6::Widgets)

# if environment is windows ha
if(WIN32)
    set_target_properties(app PROPERTIES WIN32_EXECUTABLE TRUE)
endif()



