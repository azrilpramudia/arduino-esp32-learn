void blinkLED(int count, int delayTime) {
  for (int i = 0; i < count; i++) {   // jumlah kedip sesuai parameter count
    digitalWrite(LED, HIGH);
    delay(delayTime);
    digitalWrite(LED, LOW);
    delay(delayTime);
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  blinkLED(3, 200);  // LED kedip 3 kali dengan delay 200ms
  delay(1000);

  // blinkLED(5, 500);  // LED kedip 5 kali dengan delay 500ms
  // delay(2000);
}
