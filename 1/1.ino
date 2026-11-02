// 퍼셉트론 AND 게이트
const int SW1 = D2;
const int SW2 = D3;
const int LED = LED_BUILTIN; // LD2

//XOR
float w1 = -1.0;
float w2 = -1.0;
float b = 1.5;

int perceptron(int x1, int x2)
{
  float sum = w1*x1 + w2*x2 + b;
  return (sum > 0) ? 1 : 0;
}
void setup() 
{
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() 
{
  // 누르면 LOW → 1로 뒤집기
  int x1 = (digitalRead(SW1)==LOW) ? 1 : 0;
  int x2 = (digitalRead(SW2)==LOW) ? 1 : 0;

  digitalWrite(LED, perceptron(x1, x2));
  delay(20);
}
