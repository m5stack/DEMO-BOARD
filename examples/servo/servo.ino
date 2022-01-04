#include <M5Stack.h>
#include "driver/ledc.h"

const int servo_pin = 15;
int freq = 50;
int ledChannel = 0;
int resolution = 8;
 
void setup() {
  
  M5.begin();
  M5.Lcd.setCursor(120, 110, 4);
  M5.Lcd.println("SERVO");
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(servo_pin, ledChannel);

}
 
void loop() {
 
    ledcWrite(ledChannel, 6);//0°
    delay(1000);
    ledcWrite(ledChannel, 18);//90°
    delay(1000);
    ledcWrite(ledChannel, 30);//180°
    delay(1000);
    
}
