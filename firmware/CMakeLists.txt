set(CMAKE_ARDUINO_PATH $ENV{HOME}/lib/arduino-cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_ARDUINO_PATH}/cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)

project(ardburno C CXX)

add_subdirectory(src)
