#include <WiFi.h>
#include <HTTPClient.h>

// Konfigurasi WiFi
const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";

// Firebase URL
const char* firebaseURL =
  "https://garudaoperationiot-default-rtdb.asia-southeast1.firebasedatabase.app/missions/team01.json";

// Fungsi mengirim data hotspot ke Firebase
void kirimDataHotspot() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(firebaseURL);
    http.addHeader("Content-Type", "application/json");
    String data = "{\"hotspot\":true}";

    int httpResponseCode = http.PATCH(data);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response: ");
      Serial.println(httpResponseCode);

      Serial.println("Hotspot berhasil dikirim!");
      Serial.println(http.getString());
    }
    else {
      Serial.print("Gagal mengirim data: ");
      Serial.println(httpResponseCode);
    }

    http.end();

  } else {
    Serial.println("WiFi tidak terhubung!");
  }
}

void setup() {
  Serial.begin(115200);
  // Menghubungkan WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Terhubung!");
  delay(1000);
}

void loop() {
  // Mengirim status hotspot
  kirimDataHotspot();
  delay(5000);
}
