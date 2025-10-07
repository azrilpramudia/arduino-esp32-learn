// perulangan (for loop)
#define led_pin 5

int counter = 1;

void ledBlink(int atas, int bawah) {
  for(int counter = 1; counter <= atas; counter++) {
    for(int counter2 = 1; counter2 <= bawah; counter2++) {
        digitalWrite(led_pin, HIGH);
        Serial.print("LED Menyala Ke : ");
        Serial.println(counter2);  // turn the LED on (HIGH is the voltage level)
        delay(200);   // wait for a second
                              
        digitalWrite(led_pin, LOW);
        Serial.print("LED Mati ke : ");
        Serial.println(counter2);   // turn the LED off by making the voltage LOW
        delay(200);   // wait for a second
    }
    Serial.println(" ");
    delay(1000);  // wait for a second
  }
  Serial.println("Sleeping....");
  Serial.println(" ");
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);

  ledBlink(8, 2);    
}

// the loop function runs over and over again forever
void loop() {

}
