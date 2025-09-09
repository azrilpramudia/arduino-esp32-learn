int counter = 1;

unsigned long previousMillis = 0;
const long interval = 5000;

// put your setup code here, to run once:
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); 
}

// put your main code here, to run repeatedly:
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    currentMillis = millis();

    if (counter % 2 == 0) {
    Serial.print("Lampu Nyala ");
    Serial.println(counter);
    led_lampu();
    currentMillis = millis();
  
  } else if (counter % 5 == 0) {
    Serial.print("Lampu Nyala ");
    Serial.println(counter);
    led_lampu();
    currentMillis = millis();

  } else {
    Serial.print("Lampu Mati ");
    Serial.println(counter);
    currentMillis = millis();
  }
  previousMillis = currentMillis;
  counter++;
  } 
}

void led_lampu() {
  for(int lampu = 1; lampu <= counter; lampu++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}
