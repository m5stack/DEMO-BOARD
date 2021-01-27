/*
    Description: Use ENV II Unit to read temperature, humidity 
*/
#include <M5Stack.h>
#include <Wire.h>
#include "SHT3X.h"

SHT3X sht30;
float tmp = 0.0;
float hum = 0.0;

void setup() {
  M5.begin();
  M5.Power.begin();
  Wire.begin();
  M5.Lcd.setBrightness(10);
  M5.Lcd.setTextSize(3);
  M5.Lcd.clear(BLACK);
}

void loop() {
  if(sht30.get()==0){
    tmp = sht30.cTemp;
    hum = sht30.humidity;
  }
  Serial.printf("Temperatura: %2.2f*C  Humedad: %0.2f%%\r\n", tmp, hum);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(WHITE, BLACK);
  
  M5.Lcd.printf("Temp: %2.1f  \r\nHumi: %2.0f%%  \r\n", tmp, hum);

  delay(100);
}
