#include <Arduino.h>
#include <SPI.h>

#include "config.h"

void address_bus_latch() {
  digitalWrite(ADR_RCLK, HIGH);
  digitalWrite(ADR_RCLK, LOW);
}

void address_bus_set(uint16_t value) {
  SPI.transfer(value >> 8);
  SPI.transfer(value);

  PORTC |=  0b00000100;
  PORTC &= ~0b00000100;
}
