#include <stdarg.h>

#define BAUD_RATE 115200

#define ROM_CE A3
#define ROM_OE A4
#define ROM_WE A5

#define CE(state) digitalWrite(ROM_CE, !state)
#define OE(state) digitalWrite(ROM_OE, !state)
#define WE(state) digitalWrite(ROM_WE, !state)

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 1

boolean echo = true;

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

void setup() {
  Serial.begin(BAUD_RATE);

  CE(0);
  OE(0);
  WE(0);
}

void printPrompt() {
  Serial.print("> ");
}

void loop() {
  printPrompt();

  char *input = getLine();

  dispatch(input[0], input + 1);
}

void dispatch(char cmd, char * args) {
  switch(cmd) {
    case('v'):
      commandVersion();
      break;
    default:
      commandError(cmd);
      break;
  }
}

void commandVersion() {
  pf("Version %d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
}

void commandError(char cmd) {
  pf("Don't know command '%c'.", cmd);
}

char readChar() {
  char data = (char) Serial.read();
  if (echo) {
    Serial.write(data);
    if (data == '\r') {
      Serial.write('\n');
    }
  }

  return data;
}


char * getLine() {
  static char buffer[24];
  static byte i = 0;

  while (true) {
    if (Serial.available() > 0) {
      char data = readChar();

      if (data == '\r') {
        buffer[i] = '\0';
        break;
      }

      buffer[i] = data;
      i++;
    }
  }

  i = 0;

  return buffer;
}
