// perulangan (for loop)
#define led_pin 5
int n = 1;

void ledBlink() {
  for (int i = 0; i < n; i++) {
    if(n % 2 == 0){
        digitalWrite(led_pin, HIGH);
        Serial.println("Genap");  // turn the LED on (HIGH is the voltage level)
        delay(200);
    }
        digitalWrite(led_pin, HIGH);
        Serial.println("Genap");  // turn the LED on (HIGH is the voltage level)
        delay(200);   // wait for a second
        digitalWrite(led_pin, LOW);   // turn the LED off by making the voltage LOW
        delay(200);                     // wait for a second
  }
}

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println(i);
  ledBlink();
  delay(1000);
  n++;
}
