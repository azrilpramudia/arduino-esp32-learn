// import Library
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

#define ledPin LED_BUILTIN

String msg;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  SerialBT.begin("Bluetooth-Test");
  Serial.println("Pair & connect to 'Bluetooth-Test'. Send 'on' / 'off'.");
}

void loop() {
  while (SerialBT.available()) {
    char c = (char)SerialBT.read();
    if (c == '\r') continue;
    if (c == '\n') {
      msg.trim();
      if (msg.length()) {
        if (msg.equalsIgnoreCase("on")) {
          digitalWrite(ledPin, HIGH);
          SerialBT.println("LED ON");
          Serial.println("command received: LED Menyala");
        } else if (msg.equalsIgnoreCase("off")) {
          digitalWrite(ledPin, LOW);
          SerialBT.println("LED OFF");
          Serial.println("command received: LED Mati");
        } else {
          // SerialBT.println("Unknown cmd. Use: on / off");
          SerialBT.print("You said: ");
          SerialBT.println(msg);
          Serial.print("Pesan tidak dikenal: ");
          Serial.println(msg);
        }
      }
      msg = ""; // reset buffer setelah newline
    } else {
      msg += c; // kumpulkan karakter
    }
  }

  // Seria Monitor
  while (Serial.available()){
    char c = Serial.read();
    SerialBT.write(c);
    Serial.write(c);
  }
}
