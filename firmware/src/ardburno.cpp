#include <stdio.h>
#include <Arduino.h>

#include "config.h"
#include "util.h"
#include "address_bus.h"
#include "data_bus.h"
#include "printf.h"
#include "eeprom.h"

void commandReadByte(char * args) {
  uint16_t address = fromHex(args, 2);

  uint8_t data = eeprom_read_byte(address);

  printf("%04x: %02x\n", address, data);
}

void commandWriteByte(char * args) {
  uint16_t address = fromHex(args, 2);
  uint8_t data = (uint8_t) fromHex(args + 4, 1);

  eeprom_write_byte(address, data);
}

unsigned long start = 0;

void start_timing() {
  start = millis();
}

void end_timing() {
  unsigned long total = millis() - start;

  printf("Took %lu.%03lu seconds\n", total / 1000, total % 1000);
}

void commandTest() {
  printf("Writing... ");
  start_timing();

  for (uint16_t i = 0; i < 0x8000; i++) {
    eeprom_write_byte(i, 0xff);
  }

  end_timing();

  printf("Reading... ");
  start_timing();

  for (uint16_t i = 0; i < 0x8000; i++) {
    eeprom_read_byte(i);
  }

  end_timing();
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
    case 'r':
      commandReadByte(args);
      break;
    case 'w':
      commandWriteByte(args);
      break;
    case 't':
      commandTest();
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

  CE(1);
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
