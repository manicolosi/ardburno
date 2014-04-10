set(ARDUINO_DEFAULT_BOARD uno) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified
set(ARDUINO_DEFAULT_SERIAL screen @SERIAL_PORT@ 115200)

generate_arduino_firmware(ardburno
  SRCS ardburno.cpp
       util.cpp)
