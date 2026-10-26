Uart testSerial(PA10, PA9); // RX = PA10, TX = PA9

void setup() {
  testSerial.begin(9600);
}

void loop() {
  testSerial.write('U');
  delay(10);
}