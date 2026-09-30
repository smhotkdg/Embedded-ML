
int lastSw = HIGH;
bool armed = false;
bool alarming = false;
void setup() {
  Serial.begin(9600);
  pinMode(D4, INPUT_PULLUP);  // 스위치
  pinMode(D13, OUTPUT);       // 상태 LED
}
void loop() {
  int sw = digitalRead(D4);

  if (lastSw == HIGH && sw == LOW) {   // 방금 눌림
    delay(20);
    armed = !armed;                    // 경보 ON / OFF
    digitalWrite(D13, armed);
  }
  lastSw = sw;
}


