#include <WiFi.h>

const char* ssid = "LCS-Guest";
const char* password = "lcsguestwifi2025";

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi Network....");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }

  // put your setup code here, to run once:
  Serial.println(" ");
  Serial.println("Connecting to WiFi Network");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:

}
