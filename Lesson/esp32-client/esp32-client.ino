#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32-Access-Point3";
const char* password = "123456789";

// const char* serverURL = "http://192.168.4.1/";
const char* urlTemp = "http://192.168.4.1/temperature";
const char* urlHumi = "http://192.168.4.1/humidity";
const char* urlPres = "http://192.168.4.1/pressure";

unsigned long prev = 0;
const unsigned long interval = 5000;

String httpGET(const char* url) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, url);
  int code = http.GET();
  String payload = "";
  if (code > 0) payload = http.getString();
  else {
    Serial.print("HTTP error: "); Serial.println(code);
  }
  http.end();
  return payload;
}

// put your setup code here, to run once:
void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi Network with IP Address: ");
  Serial.println(WiFi.localIP());
}

// put your main code here, to run repeatedly:
void loop() {
  unsigned long now = millis();
  if (now - prev >= interval) {
    prev = now;

    if(WiFi.status() == WL_CONNECTED) {
      // String resp = httpGET(serverURL);
      String temp = httpGET(urlTemp);
      String humi = httpGET(urlHumi);
      String pres = httpGET(urlPres);

      // Serial.print("Server response: ");
      // Serial.println(resp);
      Serial.print("Temperature: ");
      Serial.println(temp);
      Serial.print("Humidity: ");
      Serial.println(humi);
      Serial.print("Pressure: ");
      Serial.println(pres);
    } else {
      Serial.println("WiFi disconnected");
    }
  }
}
