#include <Arduino.h>

#include "config.h"

// TODO: Use data direction registers
void data_bus_output() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

// TODO: Optimize
void data_bus_write(byte value) {
  digitalWrite(D0, (bitRead(value, 0)));
  digitalWrite(D1, (bitRead(value, 1)));
  digitalWrite(D2, (bitRead(value, 2)));
  digitalWrite(D3, (bitRead(value, 3)));
  digitalWrite(D4, (bitRead(value, 4)));
  digitalWrite(D5, (bitRead(value, 5)));
  digitalWrite(D6, (bitRead(value, 6)));
  digitalWrite(D7, (bitRead(value, 7)));
}
