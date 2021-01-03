#ifndef MODULE_SSD1306_DISPLAY
#define MODULE_SSD1306_DISPLAY

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width in pixels
#define SCREEN_HEIGHT 64 // OLED display height in pixels

// ESP-WROOM-32 (Node-MCU-32S)
// Display --> ESP-WROOM-32     --> Purpose
// -------     ------------         -------
//     GND --> GND              --> Ground
//     VCC --> 3V3              --> VIN (3.3V)
//     D0  --> GPIO 18          --> SCK (SPI Clock)
//     D1  --> GPIO 23          --> SPI MOSI (Master Out Slave In [data output from master])
//     RES --> GPIO 19 (random) --> Reset (pick any free digital pin)
//     DC  --> GPIO  4 (random) --> Data/Command (pick any free digital pin)
//     CS  --> GPIO  5          --> SPI SS (Slave Select) [CS=Chip Select?]

// Declaration for SSD1306 display
#define OLED_DC     4
#define OLED_CS     5
#define OLED_RESET 19

void setup_ssd1306_module();
void drawSensorData(float temp, float hum, float pres);
void drawText(const char *text, size_t size = 1, size_t posX = 0, size_t posY = 0, bool clearDisplay = true);

#endif // MODULE_SSD1306_DISPLAY
