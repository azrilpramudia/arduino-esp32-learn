/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

#define led_pin 5

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);

  // digitalWrite(led_pin, HIGH);
  // Serial.println("LED Menyala");  // turn the LED on (HIGH is the voltage level)
  // delay(1000);                       // wait for a second
  // digitalWrite(led_pin, LOW);
  // Serial.println("LED Mati");  // turn the LED on (HIGH is the voltage level)
  // delay(1000);
  //                        // wait for a second
  // digitalWrite(led_pin, HIGH);
  // Serial.println("LED Menyala");  // turn the LED on (HIGH is the voltage level)
  // delay(1000);                       // wait for a second
  // digitalWrite(led_pin, LOW);
  // Serial.println("LED Mati");   // turn the LED off by making the voltage LOW
  // delay(1000);

  // digitalWrite(led_pin, HIGH);
  // Serial.println("LED Menyala");   // turn the LED off by making the voltage LOW
  // delay(5000);
  // digitalWrite(led_pin, LOW);
  // Serial.println("LED mati");
  // delay(1000);
  
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
  // for(int counter = 1; counter <= 3; counter++)
  // {
  //   for(int counter2 = 1; counter2 <= 10; counter2++) {
  //     digitalWrite(led_pin, HIGH);
  //     // Serial.println("LCD Menyala");
  //     Serial.println(counter2);   // turn the LED off by making the voltage LOW
  //     delay(200);
  //     digitalWrite(led_pin, LOW);
  //     Serial.println("LCD OFF");
  //     delay(200);
  //   }   
  
  // delay(1000);
  // }                     // turn the LED off by making the voltage LOW
  // Serial.println("Sleeping.....");
}
