#include <stdio.h>
#include <Arduino.h>

#include "config.h"

static FILE uartout = { 0 };

static int uart_putchar(char c, FILE *stream) {
  Serial.write(c);
  return 0;
}

void printf_setup() {
  Serial.begin(BAUD_RATE);

  fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &uartout;
}
