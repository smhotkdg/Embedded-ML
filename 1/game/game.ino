enum State { WAIT, READY, GO };
State st = WAIT;
unsigned long t0, waitMs, goTime;

// ---- D4 = 시작 버튼 (버튼 도우미, 그대로) ----
int  stable = HIGH, lastRead = HIGH;
unsigned long tChange = 0, tDown = 0;
bool justPressed = false;
unsigned long released = 0;
void readButton() {
  justPressed = false;  released = 0;
  int r = digitalRead(D4);
  if (r != lastRead) { lastRead = r; tChange = millis(); }
  if (millis() - tChange > 20 && r != stable) {
    stable = r;
    if (stable == LOW) { justPressed = true; tDown = millis(); }
    else               released = millis() - tDown;
  }
}

// ---- D6 = 반응 버튼 (새로 추가) ----
int  last6 = HIGH;
bool hit6  = false;                       // 이번 loop 에서 막 눌렸다
void readHit() {
  int r = digitalRead(D6);
  hit6 = (last6 == HIGH && r == LOW);     // HIGH → LOW 순간
  last6 = r;
}

void setup() {
  Serial.begin(9600);
  pinMode(D4, INPUT_PULLUP);    // 시작 버튼
  pinMode(D6, INPUT_PULLUP);    // 반응 버튼
  pinMode(D9, OUTPUT);
  pinMode(D13, OUTPUT);
  randomSeed(analogRead(A0));
  Serial.println("D4 를 누르면 시작!");
}

void loop() {
  readButton();  readHit();               // D4, D6 둘 다 읽기
  switch (st) {
    case WAIT:
      if (justPressed) {                  // D4 = 시작
        waitMs = random(1000, 4000);  t0 = millis();
        digitalWrite(D13, HIGH);  st = READY;
      }
      break;
    case READY:
      if (hit6) {                         // D6 = 반칙!
        Serial.println("부정출발!");  tone(D9, 200, 600);
        digitalWrite(D13, LOW);  st = WAIT;
      } else if (millis() - t0 > waitMs) {
        tone(D9, 2000);  goTime = millis();  st = GO;
      }
      break;
    case GO:
      if (hit6) {                         // D6 = 정답
        noTone(D9);  digitalWrite(D13, LOW);
        Serial.print("반응시간 ms: ");  Serial.println(millis() - goTime);
        st = WAIT;
      }
      break;
  }
}