#include <WiFi.h>
#include <PubSubClient.h>

// WIFI & MQTT
const char* ssid = "LCS-Guest";
const char* password = "lcsguestwifi2025";

const char* mqtt_server = "broker.hivemq.com";
const uint16_t mqtt_port = 1883;

// Topic
const char* topic_pub_temp = "esp32/temperature";
const char* topic_pub_humi = "esp32/humidity";
const char* topic_sub_led = "esp32/output";

#define ledPin LED_BUILTIN

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
const unsigned long interval = 5000;

void setup_wifi(){
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi Connected to IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived ["); Serial.print(topic); Serial.print("]");
  String msg;
  for(unsigned int i = 0; i < length; i++){
    char c = (char)payload[i];
    Serial.print(c);
    msg += c;
  }
  Serial.println();

  if (String(topic) == topic_sub_led) {
    if (msg == "on") {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED ON");
    } else if (msg == "off") {
      digitalWrite(ledPin, LOW);
      Serial.println("LED OFF");
    }
  }
}

void reconnect(){
  while(!client.connected()){
    Serial.print("Attempting MQTT Connection... ");

    String clientId = "ESP32Client-";
    clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

    if(client.connect(clientId.c_str())){
      Serial.println("connected");
      client.subscribe(topic_sub_led);
    } else {
      Serial.print("failed, rc="); Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// put your setup code here, to run once:
void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// put your main code here, to run repeatedly:
void loop() {
  if(!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > interval) {
    lastMsg = now;

    float temp = 25.0 + (float)(random(0, 1000)) / 100.0f;
    float humi = 40.0 + (float)(random(0, 4000)) / 100.0f;

    char tempString[8];
    char humiString[8];
    dtostrf(temp, 1, 2, tempString);
    dtostrf(humi, 1, 2, humiString);

    Serial.print("Publish temperature: "); Serial.println(tempString);
    client.publish(topic_pub_temp, tempString);

    Serial.print("Publish humidity: "); Serial.println(humiString);
    client.publish(topic_pub_humi, humiString);
  }
}
