#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266HTTPClient.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
WiFiClient client;
HTTPClient http;

const char* ssid = "U_SSID";
const char* password = "PASS-Nya";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.hostname("MeAyla");
  WiFi.begin(ssid, password);
  IPAddress ip(192, 168, 10, 77);
  IPAddress gateway(192, 168, 10, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);

  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM");
  lcd.setCursor(0, 1);      
  lcd.print("READY");
  }

void loop() {         
    if (http.begin(client, "http://47.254.194.2/data.txt")) {  // HTTP
      int httpCode = http.GET();
      if (httpCode > 0) {
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
          }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
    delay(5000);
  }
