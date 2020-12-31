#include "SSD1306_128x64_SPI.h"

#include "time.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);

void setup_ssd1306_module() {
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("Error: Could not initialize SSD1306 display!"));
    for(;;);
  }
  display.clearDisplay();
}

void drawSensorData(float temp, float hum, float pres) {
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  char now[9];
  strftime(now, sizeof(now), "%H:%M:%S", &timeinfo);

  char buffer[] = " 12:00:00 \n000.00°C\n000.00%\n0000.00hPa";
  sprintf(buffer, " %s \n%.2f C\n%.2f%%\n%.2fhPa", now, temp, hum, pres);
  drawText(buffer, 2, 0, 0, true);
}

void drawText(const char *text, size_t size, size_t posX, size_t posY, bool clearDisplay) {
  if (clearDisplay) display.clearDisplay();

  display.setTextSize(size);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(posX, posY);
  display.cp437(true);

  display.write(text);
  display.display();
}
