#ifndef MODULE_BME280_SENSOR
#define MODULE_BME280_SENSOR

#include <BME280I2C.h>
#include <Wire.h>

void setup_bcm280_module();
void printBME280Data(void (*callb) (float, float, float));

#endif // MODULE_BME280_SENSOR
