#include <Arduino.h>
#include <SPI.h>

#include "config.h"

void address_bus_latch() {
  digitalWrite(ADR_RCLK, HIGH);
  digitalWrite(ADR_RCLK, LOW);
}

void address_bus_set(uint16_t value) {
  //shiftOut(ADR_DATA, ADR_SCLK, MSBFIRST, value >> 8);
  //shiftOut(ADR_DATA, ADR_SCLK, MSBFIRST, value);
  SPI.transfer(value >> 8);
  SPI.transfer(value);

  delayMicroseconds(100);

  PORTC |=  0b00000100;
  PORTC &= ~0b00000100;

  delayMicroseconds(100);
}
