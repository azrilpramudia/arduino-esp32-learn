int counter = 1;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  if(counter % 2 == 0){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(counter);
    led_lampu();  // turn the LED on (HIGH is the voltage level)
    delay(200);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println(counter);   // turn the LED off by making the voltage LOW
    delay(1000);
  }        // wait for a second
  delay(1000);
  counter++;                        // wait for a second
}

void led_lampu(){
  for(int lampu = 1; lampu <= counter; lampu++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}
