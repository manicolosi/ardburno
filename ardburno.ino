int ADR_DATA = A0;
int ADR_SCLK = A1;
int ADR_RCLK = A2;

int SHIFT_DELAY_MS = 0;

int ROM_CE = A3;
int ROM_OE = A4;
int ROM_WE = A5;

int D0 = 2;
int D1 = 3;
int D2 = 4;
int D3 = 5;
int D4 = 6;
int D5 = 7;
int D6 = 8;
int D7 = 9;

void setup() {                
  Serial.begin(9600);

  pinMode(ADR_DATA, OUTPUT);
  pinMode(ADR_SCLK, OUTPUT);
  pinMode(ADR_RCLK, OUTPUT);
  
  Serial.print("\n\n\n");
}

unsigned int address = 0;

void loop() {
  if (address == 0x8000) {
    return;
  }

  Serial.print(address, HEX);

  for (int i = 0; i < 64; i++) {
    shiftValue(address + i);
    byte data = readData();
    Serial.print(' ');
    printHex(data);
  }

  Serial.print('\n');
  delay(0);
  address += 64;
}

void printHex(byte val) {
  if (val < 0x10) {
    Serial.print(0);
  }
  Serial.print(val, HEX);
  //Serial.print((char) val);
}

byte readData() {
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);

  digitalWrite(ROM_CE, LOW);
  digitalWrite(ROM_WE, HIGH);
  digitalWrite(ROM_OE, LOW);
  
  delay(1);

  byte val =
    (digitalRead(D0) << 7) +
    (digitalRead(D1) << 6) +
    (digitalRead(D2) << 5) +
    (digitalRead(D3) << 4) +
    (digitalRead(D4) << 3) +
    (digitalRead(D5) << 2) +
    (digitalRead(D6) << 1) +
    (digitalRead(D7) << 0);

  return val;
}

void shiftValue(unsigned int value) {
  for (int i = 15; i >= 0; i--) {
    shiftBit((value & (1<<i)) != 0);
  }
}

void shiftBit(int state) {
  digitalWrite(ADR_DATA, state);
  digitalWrite(ADR_SCLK, HIGH);
  digitalWrite(ADR_RCLK, HIGH);
  delay(SHIFT_DELAY_MS);
  digitalWrite(ADR_SCLK, LOW);
  digitalWrite(ADR_RCLK, LOW);
  delay(SHIFT_DELAY_MS);
}

