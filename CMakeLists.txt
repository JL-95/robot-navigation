cmake_minimum_required(VERSION 3.16)
project(robot_navigation VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(robobites-nav
    src/main.cpp
    src/SensorParser.cpp
    src/PathPlanner.cpp
    src/RouteCache.cpp
    src/Telemetry.cpp
)

target_include_directories(robobites-nav PRIVATE include)
