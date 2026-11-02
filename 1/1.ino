// 퍼셉트론 AND 게이트
const int SW1 = D2;
const int SW2 = D3;
const int LED = LED_BUILTIN; // LD2

// 학습 데이터 (AND)
int X[4][2] = {{0,0},{0,1},{1,0},{1,1}};
int T[4]= {0,0,0,1};

//AND
float w1 = 0;
float w2 = 0;
float b = 0;
float lr = 0.25; //학습률
void train() 
{
  for (int epoch = 1; epoch <= 20; epoch++) {
    int errors = 0;
    for (int i = 0; i < 4; i++) 
    {
      int x1 = X[i][0], x2 = X[i][1];
      int e = T[i] - predict(x1, x2);
      if (e != 0)
      {
        errors++;
      }
      w1 += lr * e * x1;
      w2 += lr * e * x2;
      b += lr * e;
    }
    printStatus(epoch, errors);
    if (errors == 0) return; // 다 맞힘!
  }
}
int predict(int x1, int x2) 
{
  return (w1*x1 + w2*x2 + b > 0) ? 1 : 0;
}

// 학습 상태를 PC 화면에 출력
void printStatus(int epoch, int errors) 
{
  Serial.print("epoch ");
  Serial.print(epoch);
  Serial.print(" err ");
  Serial.print(errors);
  Serial.print(" w1 ");
  Serial.print(w1);
  Serial.print(" w2 ");
  Serial.print(w2);
  Serial.print(" b ");
  Serial.println(b);
}



int perceptron(int x1, int x2)
{
  float sum = w1*x1 + w2*x2 + b;
  return (sum > 0) ? 1 : 0;
}
void setup() 
{
  Serial.begin(115200);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  delay(2000); // 창 열 시간

  train(); // 학습!

}

void loop() 
{
  // 누르면 LOW → 1로 뒤집기
  int x1 = (digitalRead(SW1)==LOW) ? 1 : 0;
  int x2 = (digitalRead(SW2)==LOW) ? 1 : 0;

  digitalWrite(LED, perceptron(x1, x2));
  delay(20);
}
