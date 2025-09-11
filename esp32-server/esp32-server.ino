#include <WiFi.h> // library bawaan ESP32 untuk mengatur koneksi Wi-Fi (AP/STA).
#include <WebServer.h> // library web server sederhana untuk membuat endpoint HTTP.

const char* ssid = "Beta-Server"; // nama SSID (jaringan Wi-Fi) yang akan dibuat oleh ESP32.
const char* password = "123456789"; // password untuk Wi-Fi AP tersebut (minimal 8 karakter).

WebServer server(80); // Membuat objek server di port 80 (port default HTTP).

// void handleRoot(){
//   server.send(200, "text/plain", "Server Terhubung");
// }

// Variable Data Global Dummy
float tempVal = 0; // suhu (float).
int humVal = 0; // kelembapan (integer).
float presVal = 0; // tekanan udara (float).

// Timer
unsigned long previousMillis = 0; // menyimpan waktu terakhir data diperbarui.
const unsigned long interval = 30000; // waktu update data setiap 30 detik (30.000 ms).

// put your setup code here, to run once:
void setup() {
  Serial.begin(9600); // inisialisasi komunikasi Serial dengan baudrate 9600 (untuk debug di Serial Monitor).
  Serial.println("Setting AP (Access Point)..."); // untuk memberi tahu user bahwa proses setup AP sedang berjalan.

  WiFi.mode(WIFI_AP); // Mengatur ESP32 ke mode Access Point (AP).
  if(!WiFi.softAP(ssid, password)) { // membuat Wi-Fi AP dengan SSID & password yang ditentukan.
    Serial.println("Gagal Start SoftAP"); 
    while (true) {} // Jika gagal (return false) → cetak "Gagal Start SoftAP" lalu masuk infinite loop (while(true){}) sehingga program berhenti.
  }
  
  Serial.print("AP SSID: "); Serial.println(ssid); // Cetak SSID dan alamat IP default AP (biasanya 192.168.4.1).
  Serial.print("IP Address: "); Serial.println(WiFi.softAPIP()); // IP ini dipakai client untuk mengakses server.

  // server.on("/temperature", handleRoot);

  // Endpoint / (root).
  server.on("/", [](){ 
    server.send(200, "text/plain", "Server Terhubung");
  });

  // Endpoint /temperature
  server.on("/temperature", [](){
    // float tempVal = random(30.2, 40.1);
    server.send(200, "text/plain", "Temperature: " + String(tempVal) + "°C"); // Membalas data suhu terakhir yang disimpan di variabel tempVal.
  });

  // Endpoint /humidity.
  server.on("/humidity", [](){
    // int humVal = random(20, 50);
    server.send(200, "text/plain", "Kelembapan: " + String(humVal) + "%"); // Membalas data kelembapan terakhir (humVal).
  });

  // Endpoint /pressure.
  server.on("/pressure", [](){
    // float presVal = random(10.1, 40.2);
    server.send(200, "text/plain", "Tekanan: " + String(presVal) + "hPa"); // Membalas data tekanan udara terakhir (presVal).
  });

  server.on("/all", [](){
      String data = "Data Terbaru\n\n";
      data += "Temperature: " + String(tempVal) + "°C\n";
      data += "Kelembapan: " + String(humVal) + "%\n";
      data += "Tekanan: " + String(presVal) + "hPa\n";
      server.send(200, "text/plain", data);
    });
  
  server.begin(); // menyalakan HTTP server.
  Serial.println("HTTP Server started...."); // Cetak "HTTP Server started...." untuk memberi tahu bahwa server sudah siap menerima request.
  Serial.println(" ");
}

// put your main code here, to run repeatedly:
void loop() {
  // millis() → waktu sejak board dinyalakan (dalam ms).
  // Disimpan ke now untuk dibandingkan dengan previousMillis.
  unsigned long now = millis();

  // Jika sudah lewat 30 detik sejak update terakhir, update waktu previousMillis.
  if(now - previousMillis >= interval){
    previousMillis = now;

    // Generate data dummy baru:
    tempVal = random(302, 401) / 10.0; // hasil acak 30.2 sampai 40.0 (suhu).
    humVal = random(20, 50); // hasil acak 20 sampai 49 (kelembapan).
    presVal = random(1010, 1040) / 10.0; // hasil acak 101.0 sampai 103.9 (tekanan).

    // Cetak data dummy baru ke Serial Monitor setiap kali update (30 detik sekali).
    Serial.println("DATA TERBARU");
    Serial.print("Temperature: "); Serial.println(tempVal);
    Serial.print("Humidity: "); Serial.println(humVal);
    Serial.print("Pressure: "); Serial.println(presVal);
    Serial.println("===================");
  }
  // Wajib dipanggil terus menerus.
  // Tugasnya: mengecek apakah ada client yang request, dan jika ada → jalankan handler yang sesuai.
  // Tanpa ini, server tidak akan merespons request.
  server.handleClient();
}
