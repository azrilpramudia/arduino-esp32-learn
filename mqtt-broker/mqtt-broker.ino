// Bagian Import Library
#include <WiFi.h>
#include <PubSubClient.h>

// Konfigurasi WiFi & MQTT
const char* ssid = "LCS-Guest";
const char* password = "lcsguestwifi2025";

const char* mqtt_server = "broker.hivemq.com"; // alamat broker MQTT (di sini broker publik HiveMQ).
const uint16_t mqtt_port = 1883; // port standar MQTT (tanpa TLS).

// Topic
const char* topic_pub_temp = "esp32/temperature"; // topik untuk publish data suhu.
const char* topic_pub_humi = "esp32/humidity"; // topik untuk publish data kelembapan.
const char* topic_pub_pres = "esp32/pressure"; // topik publish tekanan
const char* topic_sub_led = "esp32/led"; // topik yang disubscribe untuk mengontrol LED.

// Definisi Pin LED
// pin LED bawaan ESP32 (biasanya GPIO 2).
#define ledPin LED_BUILTIN // alias untuk LED bawaan.

// Objek WiFi & MQTT
WiFiClient espClient; // membuat koneksi TCP/IP ke broker MQTT.
PubSubClient client(espClient); // objek utama untuk publish & subscribe MQTT.

// Timer untuk publish data
unsigned long lastMsg = 0; // menyimpan waktu terakhir publish data.
const unsigned long interval = 5000; // publish setiap 5 detik sekali.

// Fungsi setup_wifi()
// Menampilkan status WiFi di Serial Monitor.
void setup_wifi(){
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); // WiFi.mode(WIFI_STA) → mode Station (ESP32 connect ke WiFi).
  WiFi.begin(ssid, password); // WiFi.begin() → mulai koneksi ke SSID dengan password.

  while(WiFi.status() != WL_CONNECTED){ // while(WiFi.status() != WL_CONNECTED) → tunggu sampai WiFi terhubung.
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi Connected to IP: ");
  Serial.println(WiFi.localIP()); // WiFi.localIP() → tampilkan alamat IP ESP32 di jaringan lokal.
}

// Fungsi callback()
// Fungsi ini otomatis dipanggil saat ada pesan masuk dari broker MQTT.
// payload → isi pesan dalam bentuk byte array.
// topic → nama topik yang diterima.
// Loop → membaca isi payload dan dikonversi ke String msg.
void callback(char* topic, byte* payload, unsigned int length) { 
  Serial.print("Message arrived ["); Serial.print(topic); Serial.print("]");
  String msg;
  for(unsigned int i = 0; i < length; i++){
    char c = (char)payload[i];
    Serial.print(c);
    msg += c;
  }
  Serial.println();

// Mengecek apakah pesan datang dari topik esp32/output.
// Jika msg == "on" → LED nyala.
// Jika msg == "off" → LED mati.
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

// Fungsi reconnect()
// Loop sampai ESP32 berhasil connect ke broker.
// clientId → ID unik berdasarkan alamat MAC ESP32.
// clientId += String((uint32_t)ESP.getEfuseMac(), HEX);
// ESP.getEfuseMac() → ambil MAC Address unik dari ESP32.
// (uint32_t)... → konversi hasilnya ke tipe 32-bit integer.
// String(..., HEX) → ubah angka tadi ke format heksadesimal (contoh: ABC123).
// clientId += ... → tambahkan ke string "ESP32Client-".
// Hasil akhir: clientId jadi unik, misalnya "ESP32Client-ABC123".

void reconnect(){
  while(!client.connected()){
    Serial.print("Attempting MQTT Connection... ");

    String clientId = "ESP32Client-";
    clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

    // Jika berhasil connect → subscribe ke topik esp32/output.
    // Jika gagal → tampilkan error code, lalu coba lagi setelah 5 detik.
    // if(client.connect(clientId.c_str())){
    // client.connect() → mencoba koneksi ke broker MQTT dengan clientId tersebut.
    // .c_str() → mengubah String (Arduino) ke const char* (yang diminta fungsi MQTT).
    // Jika berhasil connect, blok if dijalankan.
    // topic → C-string nama topik tempat pesan diterima (mis. "esp32/led").
    // payload → pointer ke array byte berisi isi pesan (tidak null-terminated).
    // length → jumlah byte valid dalam payload.

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
// Fungsi setup()
void setup() {
  Serial.begin(9600); // Inisialisasi Serial Monitor dengan baudrate 9600.

  pinMode(ledPin, OUTPUT); // Atur pin LED sebagai output, dan matikan LED di awal.
  digitalWrite(ledPin, LOW);

  // Panggil setup_wifi() → hubungkan ke WiFi.
  setup_wifi(); 
  client.setServer(mqtt_server, mqtt_port); // client.setServer() → set alamat dan port broker MQTT.
  client.setCallback(callback); // client.setCallback() → set fungsi callback untuk pesan masuk.
}

// put your main code here, to run repeatedly:
// Mengecek apakah ESP32 masih terhubung ke broker.
void loop() {
  if(!client.connected()) { // Jika tidak → panggil reconnect().
    reconnect();
  }
  client.loop(); // client.loop() → menjaga koneksi tetap aktif dan memanggil callback() jika ada pesan masuk.
  // client.loop();
  // Fungsi khusus dari PubSubClient.
  // Wajib dipanggil sesering mungkin di dalam loop().
  // Gunanya:
  // Menjaga koneksi tetap aktif (heartbeat ke broker).
  // Mengecek apakah ada pesan baru dari broker pada topik yang sudah di-subscribe.
  // Jika ada pesan → otomatis memanggil fungsi callback().


  // Hitung waktu, jika sudah lewat 5 detik (interval), maka kirim data baru.
  unsigned long now = millis();
  if (now - lastMsg > interval) {
    lastMsg = now;

    // Buat data dummy:
    // Suhu: antara 25.0 – 34.9 °C.
    // Kelembapan: antara 40.0 – 79.9 %
    float temp = 25.0 + (float)(random(0, 1000)) / 100.0f;
    float humi = 40.0 + (float)(random(0, 4000)) / 100.0f;
    float pres = 1000.0 + (float)(random(0, 200)) / 10.0f;

    // Konversi nilai float ke string (char[]) supaya bisa dikirim via MQTT.
    // dtostrf(nilai, lebar, presisi, buffer).
    char tempString[8];
    char humiString[8];
    char presString[8];

    // Apa itu dtostrf?
    // Singkatan dari Double To String (with Float support).
    // Fungsi ini dipakai di Arduino/ESP32 untuk mengubah angka float/double menjadi string (char array).
    // Kenapa perlu? Karena fungsi MQTT publish (client.publish()) butuh data dalam bentuk C-string (char[]), bukan float.

    // Parameter dtostrf
    // value → angka float/double yang mau dikonversi (temp).
    // width → lebar total minimal string (termasuk titik desimal).
    // Jika angkanya lebih panjang, lebar ini akan menyesuaikan otomatis.
    // Jika lebih kecil, hasilnya bisa tetap rapat.
    // Contoh 1 → tidak dipaksa panjang.
    // precision → jumlah digit di belakang koma.
    // 2 → hasilnya 2 angka di belakang koma.
    // buffer → tempat hasil string disimpan (array char, misalnya tempString).

    // dtostrf() dipakai untuk mengubah angka float ke string (char[]) dengan format tertentu, supaya bisa dikirim lewat Serial Monitor atau MQTT publish.
    // Angka 28.5678 diubah jadi string "28.57" (dibulatkan 2 angka desimal).
    // Disimpan di tempString → bisa dipakai untuk client.publish().
    dtostrf(temp, 1, 2, tempString);
    dtostrf(humi, 1, 2, humiString);
    dtostrf(pres, 1, 2, presString);

    // Tampilkan data suhu & kelembapan di Serial Monitor.
    // Publish data ke broker di topik masing-masing (esp32/temperature & esp32/humidity).
    Serial.print("Publish temperature: "); Serial.println(tempString);
    client.publish(topic_pub_temp, tempString);

    Serial.print("Publish humidity: "); Serial.println(humiString);
    client.publish(topic_pub_humi, humiString);

    Serial.print("Publish pressure: "); Serial.println(presString);
    client.publish(topic_pub_pres, presString);
  }
}
