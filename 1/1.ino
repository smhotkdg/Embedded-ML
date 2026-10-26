

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  Serial.println("Ready: 1=LED ON, 0=LED OFF, U=PING");
}

void loop() {
  while (Serial.available() > 0) {
    char received = Serial.read();

    // 시리얼 모니터에서 붙이는 줄바꿈은 무시
    if (received == '\r' || received == '\n') {
      continue;
    }

    Serial.print("Received: ");
    Serial.println(received);

    switch (received) {
      case '1':
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("OK: LED ON");
        break;

      case '0':
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("OK: LED OFF");
        break;

      case 'U':
        Serial.println("OK: PONG");
        break;

      default:
        Serial.println("ERROR: Unknown command");
        break;
    }
  }
}