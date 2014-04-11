set(CMAKE_ARDUINO_PATH $ENV{HOME}/lib/arduino-cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_ARDUINO_PATH}/cmake/ArduinoToolchain.cmake)


set(ARDUINO_DEFAULT_BOARD uno) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified
set(ARDUINO_DEFAULT_SERIAL screen @SERIAL_PORT@ 115200)

# Quiet warning when building arduino firmware
set(ARDBURNO_CXX_FLAGS "-Wno-attributes")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARDBURNO_CXX_FLAGS}")

cmake_minimum_required(VERSION 2.8)

project(ardburno C CXX)

generate_arduino_firmware(ardburno
  SRCS src/ardburno.cpp
       src/util.cpp
       src/address_bus.cpp
       src/data_bus.cpp
       src/printf.cpp
       src/eeprom.cpp)
