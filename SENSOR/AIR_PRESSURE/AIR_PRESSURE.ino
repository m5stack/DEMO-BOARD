#include <M5Stack.h>
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>

/*
    note: need add library Adafruit_BMP280 from library manage
*/

Adafruit_BMP280 bme;
void setup() {
  // put your setup code here, to run once:
   M5.begin();
   Wire.begin();

   M5.Lcd.setCursor(70, 0, 4);
   M5.Lcd.print("AIR_PRESSURE");

   if (!bme.begin(0x76)){  
      Serial.println("Could not find a valid BMP280 sensor, check wiring!");
      while (1);
    }

}

void loop() {
  // put your main code here, to run repeatedly:
  float pressure = bme.readPressure();
  M5.Lcd.setCursor(50, 100, 4);
  M5.Lcd.printf("Pressure:%2.0fPa\r\n",pressure);
  delay(100); 
}
