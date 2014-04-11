#include <stdio.h>
#include <Arduino.h>

#include "config.h"
#include "util.h"
#include "address_bus.h"
#include "data_bus.h"
#include "printf.h"

void commandShift(char * args) {
  unsigned int address = fromHex(args, 2);

  address_bus_set(address);
}

void commandData(char * args) {
  byte value = (byte) fromHex(args, 1);

  data_bus_output();
  data_bus_write(value);
}

void commandVersion() {
  printf("Version %d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
}

void commandError(char cmd) {
  printf("Don't know command '%c'\n", cmd);
}

void dispatch(char cmd, char * args) {
  switch(cmd) {
    case 'v':
      commandVersion();
      break;
    case 's':
      commandShift(args);
      break;
    case 'd':
      commandData(args);
      break;
    default:
      commandError(cmd);
      break;
  }
}

void signal_setup() {
  pinMode(ADR_DATA, OUTPUT);
  pinMode(ADR_SCLK, OUTPUT);
  pinMode(ADR_RCLK, OUTPUT);

  pinMode(ROM_CE, OUTPUT);
  pinMode(ROM_OE, OUTPUT);
  pinMode(ROM_WE, OUTPUT);

  CE(0);
  OE(0);
  WE(0);
}

void setup() {
  printf_setup();
  signal_setup();
}

void loop() {
  printPrompt();

  char *input = getLine();

  dispatch(input[0], input + 1);
}
