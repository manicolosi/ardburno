#include <Arduino.h>

#include "config.h"

void address_bus_clock() {
  digitalWrite(ADR_SCLK, HIGH);
  digitalWrite(ADR_SCLK, LOW);
}

void address_bus_latch() {
  digitalWrite(ADR_RCLK, HIGH);
  digitalWrite(ADR_RCLK, LOW);
}

void address_bus_set(unsigned int value) {
  for(int i = 15; i >= 0; i--) {
    digitalWrite(ADR_DATA, bitRead(value, i) != 0);
    address_bus_clock();
  }

  address_bus_latch();
}
