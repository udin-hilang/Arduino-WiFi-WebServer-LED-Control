#include <WiFi.h>
#include <WebServer.h>

int pin[4] = {4, 17, 18, 21};      // Pin LED
String cmd = "", ssid = "realme 12+ 5G", pw = "";

WebServer server(80);              // Web server di port 80


void handleRoot() {
  // Halaman utama / petunjuk route
  server.send(200, "text/plain", "Wellcome... untuk menyalakan LED buka (ip)/H, untuk mematikan LED buka (ip)/L");
}

void handleHigh() {
  // Nyalakan semua LED
  server.send(200, "text/plain", "LED DINYALAKAN");

  int i;
  for (i = 0; i < 4; i++) {
    digitalWrite(pin[i], HIGH);
    delay(100);
  }
}

void handleLow() {
  // Matikan semua LED
  server.send(200, "text/plain", "LED DIMATIKAN");

  int i;
  for (i = 0; i < 4; i++) {
    digitalWrite(pin[i], LOW);
    delay(100);
  }
}


void setup() {
  int i;

  // Set semua pin LED sebagai output
  for (i = 0; i < 4; i++) {
    pinMode(pin[i], OUTPUT);
  }

  Serial.begin(9600);

  // Mulai koneksi ke WiFi
  WiFi.begin(ssid, pw);
  Serial.printf("\n\n\n\nTrying to Connect to ");
  Serial.println(ssid);  

  // Tunggu sampai konek
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.printf("\nConnected!\n");

  // Indikator konek (LED nyala bergantian)
  for (i = 0; i < 4; i++) {
    digitalWrite(pin[i], HIGH);
    delay(100);
    digitalWrite(pin[i], LOW);
  }

  // Daftar route
  server.on("/", handleRoot);
  server.on("/H", handleHigh);
  server.on("/L", handleLow);

  // Mulai server
  server.begin();
  Serial.println("Server ready");
}

void loop() {
  // Cek input dari serial
  if (Serial.available()) {
    cmd = Serial.readString();
    cmd.trim();
    Serial.println(cmd);

    // Ketik "1" buat lihat info WiFi
    if (cmd == "1") {
      Serial.printf("\n\nWiFi tersambung ke :\nSSID : ");
      Serial.println(WiFi.SSID());
      Serial.print("IP : ");
      Serial.println(WiFi.localIP());
      cmd = "";
    }
  }

  // Handle request dari browser
  server.handleClient();
}