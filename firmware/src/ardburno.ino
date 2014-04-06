#include <stdarg.h>

#define BAUD_RATE 115200

#define ADR_DATA A0
#define ADR_SCLK A1
#define ADR_RCLK A2

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

  signalSetup();

  CE(0);
  OE(0);
  WE(0);
}

void signalSetup() {
  pinMode(ADR_DATA, OUTPUT);
  pinMode(ADR_SCLK, OUTPUT);
  pinMode(ADR_RCLK, OUTPUT);
  pinMode(ROM_CE, OUTPUT);
  pinMode(ROM_OE, OUTPUT);
  pinMode(ROM_WE, OUTPUT);
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
    case 'v':
      commandVersion();
      break;
    case 's':
      commandShift(args);
      break;
    default:
      commandError(cmd);
      break;
  }
}

void commandShift(char * args) {
  char input[7] = "0x1234";

  for (int i = 0; i < 4; i++) {
    if (args[i] == '\0') {
      input[i+2] = '\0';
      break;
    }

    input[i+2] = args[i];
  }

  unsigned int address;
  sscanf(input, "%x", &address);

  shift(address);
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
