#include <M5Stack.h>
#include "DHT12.h"
#include <Wire.h> //The DHT12 uses I2C comunication.

DHT12 dht12; //Preset scale CELSIUS and ID 0x5c.

void setup() {
    M5.begin();
    Wire.begin();
    M5.Lcd.setCursor(80, 0, 4);
    M5.Lcd.print("TEMPERATURE");
}

void loop() {
 
    float tmp = dht12.readTemperature();
    float hum = dht12.readHumidity();
    M5.Lcd.setCursor(30, 100, 4);
    M5.Lcd.printf("Temp: %2.1f  Humi: %2.0f%%", tmp, hum);

    delay(100);
}
