int 
void LedBlink() {
    for()
}
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println();
  LedBlink();
  delay(1000);
  counter++; // wait for a second
}
