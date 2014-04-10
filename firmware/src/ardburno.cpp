#include <Arduino.h>

#include "config.h"
#include "util.h"

void signalSetup() {
  pinMode(ADR_DATA, OUTPUT);
  pinMode(ADR_SCLK, OUTPUT);
  pinMode(ADR_RCLK, OUTPUT);

  pinMode(ROM_CE, OUTPUT);
  pinMode(ROM_OE, OUTPUT);
  pinMode(ROM_WE, OUTPUT);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  CE(0);
  OE(0);
  WE(0);
}

void clock() {
  digitalWrite(ADR_SCLK, HIGH);
  digitalWrite(ADR_SCLK, LOW);
}

void latch() {
  digitalWrite(ADR_RCLK, HIGH);
  digitalWrite(ADR_RCLK, LOW);
}

void shift(unsigned int value) {
  for(int i = 15; i >= 0; i--) {
    digitalWrite(ADR_DATA, bitRead(value, i) != 0);
    clock();
  }

  latch();
}

void data(byte value) {
  digitalWrite(D0, (bitRead(value, 0)));
  digitalWrite(D1, (bitRead(value, 1)));
  digitalWrite(D2, (bitRead(value, 2)));
  digitalWrite(D3, (bitRead(value, 3)));
  digitalWrite(D4, (bitRead(value, 4)));
  digitalWrite(D5, (bitRead(value, 5)));
  digitalWrite(D6, (bitRead(value, 6)));
  digitalWrite(D7, (bitRead(value, 7)));
}

void commandShift(char * args) {
  unsigned int address = fromHex(args, 2);

  shift(address);
}

void commandData(char * args) {
  byte value = (byte) fromHex(args, 1);

  data(value);
}

void commandVersion() {
  pf("Version %d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
}

void commandError(char cmd) {
  pf("Don't know command '%c'.", cmd);
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

void setup() {
  Serial.begin(BAUD_RATE);

  signalSetup();
}

void loop() {
  printPrompt();

  char *input = getLine();

  dispatch(input[0], input + 1);
}
