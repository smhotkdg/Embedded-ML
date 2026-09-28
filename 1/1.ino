//디버깅 테스트
// int number =0;

// void setup() {
//   pinMode(D13, OUTPUT);          // PA5 — 보드의 초록 LED LD2
//   Serial.begin(9600);
// }

// void loop() {
//   digitalWrite(D13, HIGH); 
//   number++;
//   delay(500);
//   digitalWrite(D13, LOW); 
//   delay(1000);
//   Serial.println("*********");
// }


// void setup() {
//   Serial.begin(9600);
//   pinMode(D9, OUTPUT);
// }                            // 풀업은 필요 없습니다
// void loop() {
//   tone(D9, 1000);   // 패시브
//   digitalWrite(D9, HIGH);  
// }





int lastSw = HIGH;
bool armed = false, alarming = false;
int threshold = 300;          // 실측해서 정하기
void setup() {
  Serial.begin(9600);
  pinMode(D4, INPUT_PULLUP);  // 스위치
  pinMode(D9, OUTPUT);        // 부저
  pinMode(D13, OUTPUT);       // 상태 LED
}
void loop() {
  int sw = digitalRead(D4);
  
  if (lastSw == HIGH && sw == LOW) {   // 방금 눌림
    delay(20);
    armed = !armed;                    // 경보 ON / OFF
    digitalWrite(D13, armed);
    if (!armed) 
    { 
        noTone(D9);
        alarming = false; 
    }
  }
  lastSw = sw;
  int v = analogRead(A0);
  Serial.println(v);
  Serial.println(armed);
  if (armed) 
  {                         // 히스테리시스
    if (!alarming && v < threshold - 50)
    { 
        alarming = true;  
        tone(D9, 1000);
          
        digitalWrite(D9, HIGH);  
        Serial.println("start");
    }
    if ( alarming && v > threshold + 50) 
    { 
        alarming = false; 
        noTone(D9);
        digitalWrite(D9, LOW);  
        Serial.println("end");
    }
  }
  delay(50);
}


