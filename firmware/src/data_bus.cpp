#include <Arduino.h>

#include "config.h"

// TODO: Use data direction registers
void data_bus_output() {
  DDRD |= 0b11111100;
  DDRC |= 0b00000011;
}

void data_bus_input() {
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
}

uint8_t data_bus_read() {
  WE(0);
  OE(1);
  uint8_t data = ((PIND & 0b11111100) >> 2) + ((PINB & 0b00000011) << 6);
  OE(0);

  return data;
}

void poll(uint8_t value) {
  unsigned long start = millis();

  data_bus_input();
  while (data_bus_read() != value) {
    if (millis() - start > 10) {
      digitalWrite(13, HIGH);
      break;
    }
  }
  digitalWrite(13, LOW);
}

// TODO: Optimize
void data_bus_write(uint8_t value) {
  digitalWrite(D0, (bitRead(value, 0)));
  digitalWrite(D1, (bitRead(value, 1)));
  digitalWrite(D2, (bitRead(value, 2)));
  digitalWrite(D3, (bitRead(value, 3)));
  digitalWrite(D4, (bitRead(value, 4)));
  digitalWrite(D5, (bitRead(value, 5)));
  digitalWrite(D6, (bitRead(value, 6)));
  digitalWrite(D7, (bitRead(value, 7)));

  WE(1);
  WE(0);

  //delay(10);
  poll(value);
}
