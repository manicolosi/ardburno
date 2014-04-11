#include <Arduino.h>

void printPrompt() {
  Serial.print("> ");
}

char readChar() {
  char data = (char) Serial.read();

  Serial.write(data);
  if (data == '\r') {
    Serial.write('\n');
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
