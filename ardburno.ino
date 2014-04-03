int ADR_DATA = A0;
int ADR_SCLK = A1;
int ADR_RCLK = A2;

void setup() {                
  pinMode(ADR_DATA, OUTPUT);
  pinMode(ADR_SCLK, OUTPUT);
  pinMode(ADR_RCLK, OUTPUT);
  shiftValue(4456);
}

void loop() {
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
  delay(100);
  digitalWrite(ADR_SCLK, LOW);
  digitalWrite(ADR_RCLK, LOW);
  delay(100);
}
