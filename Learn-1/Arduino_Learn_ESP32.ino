#define led_pin 5

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
     // turn the LED off by making the voltage LOW
    for(int counter = 1; counter <= 3; counter++)
  {
    for(int counter2 = 1; counter2 <= 10; counter2++) {
      digitalWrite(led_pin, HIGH);
      // Serial.println("LCD Menyala");
      Serial.print("LCD Menyala : ");
      Serial.println(counter2);   // turn the LED off by making the voltage LOW
      delay(200);
      digitalWrite(led_pin, LOW);
      Serial.println("LCD OFF");
      delay(200);
    }   
  Serial.println(" ");
  delay(1000);
  }                     // turn the LED off by making the voltage LOW
  Serial.println("Sleeping.....");
  Serial.println(" ");
}

// the loop function runs over and over again forever
void loop() {
}
