#include <stdarg.h>

#define BAUD_RATE 115200

#define ADR_DATA A0
#define ADR_SCLK A1
#define ADR_RCLK A2

#define D0 2
#define D1 3
#define D2 4
#define D3 5
#define D4 6
#define D5 7
#define D6 8
#define D7 9

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


void printPrompt() {
  Serial.print("> ");
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

unsigned int fromHex(char * hex, byte size) {
  char buffer[7] = "0x\0\0\0\0";
  unsigned int address;

  for (int i = 0; i < (size * 2); i++) {
    if (hex[i] == '\0') {
      buffer[i+2] = '\0';
      break;
    }

    buffer[i+2] = hex[i];
  }

  sscanf(buffer, "%x", &address);

  return address;
}

/* Entry */

void setup() {
  Serial.begin(BAUD_RATE);

  signalSetup();
}

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
    case 'd':
      commandData(args);
      break;
    default:
      commandError(cmd);
      break;
  }
}

/* Commands */

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

/* Interfacing */

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
