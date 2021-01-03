#include "BME_280_I2C.h"
#include "SSD1306_128x64_SPI.h"

#include "secrets.h"

#include <WiFi.h>
#include "time.h"

#define SERIAL_BAUD 115200
#define LOOP_INTERVAL 1000

#ifndef LED_BUILTIN
// Builtin LED for ESP-WROOM-32 DevBoard
#define LED_BUILTIN 2
// Builtin LED for WEMOS LoLin32 DevBoard
// #define LED_BUILTIN 5
// Builtin LED for ESP32 NodeMCU DevBoard
// #define LED_BUILTIN 22
#endif // LED_BUILTIN

const char* NTP_SERVER = "pool.ntp.org";
const long  UTC_OFFSET = 3600;             // Offset between Universal Time and your time zone
const int   DAYLIGHT_SAVING_OFFSET = 3600; // Offset bewteen normal time and summer time
                                           // (3600 seconds = 1 hour)

void setup(){
  Serial.begin(SERIAL_BAUD);
  pinMode(LED_BUILTIN, OUTPUT);

  setup_bcm280_module();
  setup_ssd1306_module();

  drawText("Initia-\n"
           "lizing\n" 
           "Wifi and\n"
           "clock...",
           2);
  delay(500);

  // Wifi setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, 1);
    delay(500);
    digitalWrite(LED_BUILTIN, 0);
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.printf("Connected to Wifi network %s (%s).\n", WIFI_SSID, WiFi.localIP().toString().c_str());

  // Get real time via NTP
  configTime(UTC_OFFSET, DAYLIGHT_SAVING_OFFSET, NTP_SERVER);
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Error: Failed to initialize RTC!");
    return;
  }
  Serial.println(&timeinfo, "RTC initialized at %A, %B %d %Y %H:%M:%S");
  
  // Disconnect Wifi -- the time should be correct now!
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

unsigned long previousMillis = 0;

void loop(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= LOOP_INTERVAL) {
    previousMillis = previousMillis + LOOP_INTERVAL;

    digitalWrite(LED_BUILTIN, HIGH);
    printBME280Data(&printSensorData);
#ifdef MODULE_SSD1306_DISPLAY
    printBME280Data(&drawSensorData);
#endif // MODULE_SSD1306_DISPLAY
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void printSensorData(float temp, float hum, float pres) {
  Serial.printf("%.2f°C    %.2f%%    %.3fhPa\n", temp, hum, pres);
}
