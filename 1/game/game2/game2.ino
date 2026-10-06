enum State { LOCKED, GRACE, ALARM, OPENED };
int  stable = HIGH, lastRead = HIGH;
unsigned long tChange = 0, tDown = 0;
bool justPressed = false;     // 이번 loop 에서 막 눌렸다
unsigned long released = 0;   // 이번 loop 에서 막 뗐다 → 누른 시간(ms)
 
void readButton() {
  justPressed = false;  released = 0;
  int r = digitalRead(D4);
  if (r != lastRead) { lastRead = r; tChange = millis(); }
  if (millis() - tChange > 20 && r != stable) {   // 20ms 조용 = 진짜
    stable = r;
    if (stable == LOW) { justPressed = true; tDown = millis(); }
    else               released = millis() - tDown;
  }
}

State st = LOCKED;
int closedVal;               // 닫혔을 때의 빛
int code = 0, n = 0;         // 쌓인 암호, 누른 횟수
const int SECRET = 121;      // 짧게·길게·짧게
unsigned long t0;
// ← 여기에 '버튼 도우미' (readButton) 붙여 넣기
bool isOpen() { return abs(analogRead(A0) - closedVal) > 150; }
void readCode() {
  if (released > 0) {                 // 방금 뗐다
    if (released < 400) code = code * 10 + 1;
    else                code = code * 10 + 2;
    n++;  Serial.println(code);
  }
}
void setup() {
  Serial.begin(9600);  pinMode(D4, INPUT_PULLUP);
  pinMode(D9, OUTPUT);  pinMode(D13, OUTPUT);
  delay(1000);                  // 뚜껑 닫고 1초 기다리기
  closedVal = analogRead(A0);
}
void loop() {
  readButton();  readCode();
  switch (st) {
    case LOCKED:                                 // ● 감시
      code = 0;  n = 0;
      if (isOpen()) { st = GRACE;  t0 = millis(); }
      break;
    case GRACE:                                  // ● 유예 5초
      digitalWrite(D13, (millis() / 250) % 2);   // 깜빡깜빡
      if (n == 3 && code == SECRET) st = OPENED;
      else if (n == 3 || millis() - t0 > 5000) { tone(D9, 3000); st = ALARM; }
      break;
    case ALARM:                                  // ● 경보
      if (n == 3) {
        if (code == SECRET) { noTone(D9);  st = OPENED; }
        code = 0;  n = 0;                        // 다시 기회
      }
      break;
    case OPENED:                                 // ● 열림
      digitalWrite(D13, HIGH);
      if (!isOpen()) { digitalWrite(D13, LOW);  st = LOCKED; }
      break;
  }
}
