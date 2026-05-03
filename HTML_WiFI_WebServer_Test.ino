#include <WiFi.h>
#include <WebServer.h>

int pin[4] = {4, 17, 18, 21};      // Pin output LED
String cmd = "", ssid = "realme 12+ 5G", pw = "";  // WiFi credential

WebServer server(80);              // Web server di port 80


void handleRoot() {
  // Halaman utama (UI kontrol LED)
  String html = R"rawliteral(
    <html>
    <head>
      <style>
        button {
          font-size : 100px;
          padding : 5% 8%;
          border-radius : 10%;
        }
        body {
          background-color : lightblue;
        }
      </style>
    </head>
      <title>
        KONTROL LED
      </title>
      <h1 align="center" style="font-size : 100px;"><b>KONTROL LED</b></h1>
      <body>
        <center>
          <a href="/H"><button style="background-color : green;">ON</button></a>
          <a href="/L"><button style="background-color : red;">OFF</button></a>
        </center>
      </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html); // kirim halaman ke browser
}

void handleHigh() {
  // Menyalakan semua LED
  server.sendHeader("Location", "/");
  server.send(303);

  int i;
  for (i = 0; i < 4; i++) {
    digitalWrite(pin[i], HIGH);
    delay(100);
  }
}

void handleLow() {
  // Mematikan semua LED
  server.sendHeader("Location", "/");
  server.send(303);

  int i;
  for (i = 0; i < 4; i++) {
    digitalWrite(pin[i], LOW);
    delay(100);
  }
}


void setup() {
  int i;

  // Set semua pin sebagai output
  for (i = 0; i < 4; i++) {
    pinMode(pin[i], OUTPUT);
  }

  Serial.begin(9600);

  // Koneksi ke WiFi
  WiFi.begin(ssid, pw);
  Serial.printf("\n\n\n\nConnecting to ");
  Serial.println(ssid);

  // Tunggu sampai terhubung
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.printf("\nConnected!\n");

  // Indikator koneksi (LED blink sekali)
  for (i = 0; i < 4; i++) {
    digitalWrite(pin[i], HIGH);
    delay(100);
    digitalWrite(pin[i], LOW);
  }

  // Routing web server
  server.on("/", handleRoot);
  server.on("/H", handleHigh);
  server.on("/L", handleLow);

  // Start server
  server.begin();
  Serial.println("Server ready");
}

void loop() {
  // Input debug via Serial Monitor
  if (Serial.available()) {
    cmd = Serial.readString();
    cmd.trim();
    Serial.println(cmd);

    // Command "1" untuk cek status WiFi
    if (cmd == "1") {
      Serial.printf("\nWiFi status:\nSSID: ");
      Serial.println(WiFi.SSID());
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
      cmd = "";
    }
  }

  // Handle client request dari browser
  server.handleClient();
}