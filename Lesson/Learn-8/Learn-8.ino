void blinkLED(int count, int delayTime) {
  for (int i = 0; i < count; i++) { 
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("ON");
    delay(delayTime);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("OFF");
    delay(delayTime);
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  blinkLED(5, 500); 
  Serial.println("Done....");
  delay(1000);

  // blinkLED(5, 500); 
  // delay(2000);
}
