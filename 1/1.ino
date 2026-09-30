int lastSw = HIGH;
bool armed = false;
bool alarming = false;
void setup() {
  Serial.begin(9600);
  pinMode(D4, INPUT_PULLUP);  // 스위치
  
  pinMode(D13, OUTPUT);       // 상태 LED
}
void loop() 
{
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
  //버튼이 눌려있다면 실행 한다
  if(armed)
  {
    int v = analogRead(A0);
    Serial.println(v);
    Serial.println(armed);
  }
}





// int lastSw = HIGH;
// bool armed = false;
// bool alarming = false;
// void setup() {
//   Serial.begin(9600);
//   pinMode(D4, INPUT_PULLUP);  // 스위치
  
//   pinMode(D13, OUTPUT);       // 상태 LED
// }
// void loop() {
//   int sw = digitalRead(D4);
  
//   if (lastSw == HIGH && sw == LOW) {   // 방금 눌림
//     delay(20);
//     armed = !armed;                    // 경보 ON / OFF
//     digitalWrite(D13, armed);
//     if (!armed) 
//     { 
//         noTone(D9);
//         alarming = false; 
//     }
//   }
//   lastSw = sw;
//   //버튼이 눌려있다면 실행 한다
//   if(armed)
//   {
//     int v = analogRead(A0);
//     Serial.println(v);
//     Serial.println(armed);
//   }
  
//   if (armed) 
//   {                         // 히스테리시스
//     if (!alarming && v < threshold - 50)
//     { 
//         alarming = true;  
//         tone(D9, 1000);
          
//         digitalWrite(D9, HIGH);  
//         Serial.println("start");
//     }
//     if ( alarming && v > threshold + 50) 
//     { 
//         alarming = false; 
//         noTone(D9);
//         digitalWrite(D9, LOW);  
//         Serial.println("end");
//     }
//   }
//   delay(50);
// }




