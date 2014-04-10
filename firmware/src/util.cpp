#include <Arduino.h>
#include <stdarg.h>

/* Utilities */

void p(char *string) {
  Serial.println(string);
}

void pf(char *fmt, ... ) {
  static char buf[128];

  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, 128, fmt, args);
  va_end(args);

  p(buf);
}
