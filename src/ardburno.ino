#define BAUD_RATE 115200

#define ROM_CE A3
#define ROM_OE A4
#define ROM_WE A5

#define CE(state) digitalWrite(ROM_CE, !state)
#define OE(state) digitalWrite(ROM_OE, !state)
#define WE(state) digitalWrite(ROM_WE, !state)

boolean echo = true;

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
  Serial.println(input);
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
