#define ADR_DATA A0
#define ADR_SCLK A1
#define ADR_RCLK A2

#define ROM_CE A3
#define ROM_OE A4
#define ROM_WE A5

#define D0 2
#define D1 3
#define D2 4
#define D3 5
#define D4 6
#define D5 7
#define D6 8
#define D7 9

#include <stdarg.h>
void p(char *fmt, ... ){
  static char buf[128];
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, 128, fmt, args);
  va_end (args);
  Serial.print(buf);
}

unsigned long start = 0;

void setup() {                
  Serial.begin(115200);

  pinMode(ADR_DATA, OUTPUT);
  pinMode(ADR_SCLK, OUTPUT);
  pinMode(ADR_RCLK, OUTPUT);
  pinMode(ROM_CE, OUTPUT);
  pinMode(ROM_OE, OUTPUT);
  pinMode(ROM_WE, OUTPUT);

  romSignalSetup();

  Serial.print("\n\n\n");
}

void romSignalSetup() {
  digitalWrite(ROM_OE, HIGH);
  digitalWrite(ROM_WE, HIGH);
  digitalWrite(ROM_CE, LOW);
}

void printTime() {
  unsigned long now = millis();
  unsigned int total_seconds = (now - start) / 1000;
  unsigned int total_millis = (now - start) % 1000;
  p("Took %d.%03d seconds.\n", total_seconds, total_millis);
}

boolean done = false;

void loop() {
  if (done) {
    //digitalWrite(ROM_WE, HIGH);
    //digitalWrite(ROM_OE, LOW);
    //shiftValue(1);
    //p(" %02X\n", readByte());
    return;
  }

  start = millis();
  writeRom();
  printTime();

  delay(100);
  
  start = millis();
  readRom(0x0100);
  printTime();

  done = true;
}

#define COLUMNS 64

void readRom(unsigned int count) {
  readSetup();

  for(unsigned int i = 0; i < count; i += COLUMNS) {
    p("%04X", i);

    for (int j = 0; j < COLUMNS; j++) {
      shiftValue(i + j);
      p(" %02X", readByte());
    }

    Serial.print('\n');
  }
}

#define BYTE_TO_WRITE 33

void writeRom() {
  writeSetup();

  for(unsigned int i = 0; i < 0x0100; i += COLUMNS) {
    if (i % 0x1000 == 0) {
      p("\n%04X ", i);
    }

    for (int j = 0; j < COLUMNS; j++) {
      writeByte(i + j, BYTE_TO_WRITE);
    }

    Serial.print('.');
  }

  Serial.print('\n');
}

void readSetup() {
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);

  digitalWrite(ROM_WE, HIGH);
  digitalWrite(ROM_OE, LOW);
}

void writeSetup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  digitalWrite(ROM_OE, HIGH);
  digitalWrite(ROM_WE, HIGH);
}

void writeByte(unsigned int address, byte value) {
  shiftValue(address);

  delay(5); // tADH
  
  digitalWrite(ROM_WE, LOW);

  digitalWrite(D0, (bitRead(value, 0)));
  digitalWrite(D1, (bitRead(value, 1)));
  digitalWrite(D2, (bitRead(value, 2)));
  digitalWrite(D3, (bitRead(value, 3)));
  digitalWrite(D4, (bitRead(value, 4)));
  digitalWrite(D5, (bitRead(value, 5)));
  digitalWrite(D6, (bitRead(value, 6)));
  digitalWrite(D7, (bitRead(value, 7)));

  delay(5); // tWP

  digitalWrite(ROM_WE, HIGH);

  delay(15); // ?
}

byte readByte() {
  return ((PIND & 0b11111100) >> 2) +
    ((PINB & 0b00000011) << 6);
}

void shiftValue(unsigned int value) {
  for (int i = 15; i >= 0; i--) {
    digitalWrite(ADR_DATA, bitRead(value, i) != 0);
    digitalWrite(ADR_SCLK, HIGH);
    digitalWrite(ADR_SCLK, LOW);
  }
  digitalWrite(ADR_RCLK, HIGH);
  digitalWrite(ADR_RCLK, LOW);
}

