set(CMAKE_ARDUINO_PATH $ENV{HOME}/lib/arduino-cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_ARDUINO_PATH}/cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)

project(ardburno C CXX)

# Quiet warning when building arduino firmware
set(ARDBURNO_CXX_FLAGS "-Wno-attributes")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARDBURNO_CXX_FLAGS}")

add_subdirectory(src)
