#include <WiFi.h>
#include <WebServer.h>

int pin[4] = {4, 17, 18, 21};   // Pin LED

WebServer server(80);           // Web server di port 80


void handleRoot() {
  // Halaman utama / petunjuk route
  server.send(200, "text/plain", "Wellcome... untuk menyalakan LED buka 192.168.4.1/H, untuk mematikan LED buka 192.168.4.1/L");
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

  // Aktifkan ESP32 sebagai hotspot
  WiFi.softAP("Test");

  // Tampilkan info hotspot
  Serial.printf("\n\nHotspot diaktifkan\nSSID : ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("IP : ");
  Serial.println(WiFi.softAPIP());

  // Daftar route
  server.on("/", handleRoot);
  server.on("/H", handleHigh);
  server.on("/L", handleLow);

  // Mulai server
  server.begin();
  Serial.println("Server ready");
}

void loop() {
  // Handle request dari browser
  server.handleClient();
}