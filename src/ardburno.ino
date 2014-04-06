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

char * getLine() {
  static char buffer[24];
  static byte i = 0;

  while (true) {
    if (Serial.available() > 0) {
      char data = (char) Serial.read();

      if (data == '\r') {
        buffer[i] = '\0';
        Serial.print("\r\n");
        break;
      }

      if (echo) {
        Serial.print(data);
      }

      buffer[i] = data;
      i++;
    }
  }

  return buffer;
}
