cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(gameOfLife)

include_directories(${PROJECT_SOURCE_DIR}/includes)
file(GLOB SOURCES "src/*.cpp")

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

add_executable(gameOfLife ${SOURCES})
target_link_libraries(gameOfLife sfml-graphics sfml-window)

file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
