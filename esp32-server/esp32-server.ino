#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-Access-Point2";
const char* password = "123456789";

WebServer server(80);

// String tempVal = "35";
// String humVal = "60.2";
// String presVal = "1004.1";

// void handleRoot(){
//   server.send(200, "text/plain", "Server Terhubung");
// }

// put your setup code here, to run once:
void setup() {
  Serial.begin(9600);
  Serial.println("Setting AP (Access Point)...");

  WiFi.mode(WIFI_AP);
  if(!WiFi.softAP(ssid, password)) {
    Serial.println("Gagal Start SoftAP");
    while (true) {}
  }
  
  Serial.print("AP SSID: "); Serial.println(ssid);
  Serial.print("IP Address: "); Serial.println(WiFi.softAPIP());

  // server.on("/temperature", handleRoot);

  server.on("/", [](){
    server.send(200, "text/plain", "Server Terhubung");
  });
  server.on("/temperature", [](){
    float tempVal = random(30.2, 40.1);
    server.send(200, "text/plain", "Temperature: " + String(tempVal) + "*C");
  });
  server.on("/humidity", [](){
    int humVal = random(20, 50);
    server.send(200, "text/plain", "Kelembapan: " + String(humVal) + "%");
  });
  server.on("/pressure", [](){
    float presVal = random(10.1, 40.2);
    server.send(200, "text/plain", "Tekanan: " + String(presVal) + "hPa");
  });
  
  server.begin();
  Serial.println("HTTP Server started....");
  
}

// put your main code here, to run repeatedly:
void loop() {
  server.handleClient();
}
