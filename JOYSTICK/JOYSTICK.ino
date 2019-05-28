#include <M5Stack.h>

/*
  note:Reading the adc value requires writing the pin 25 of the adc to 0.
  dacWrite(25, 0);
*/

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  pinMode(2, INPUT_PULLUP);
  dacWrite(25, 0);

  M5.Lcd.setCursor(100, 0, 4);
  M5.Lcd.print("JOYSTICK");
}

uint16_t x_data;
uint16_t y_data;
uint8_t button_data;
void loop() {
  // put your main code here, to run repeatedly:
  x_data = analogRead(35);
  y_data = analogRead(36);
  button_data = digitalRead(2);

  Serial.printf("x:%0d y:%0d button:%d\n", x_data, y_data, button_data);

  M5.Lcd.setCursor(30, 120, 4);
  M5.Lcd.printf("x:%04d y:%04d button:%d\n", x_data, y_data, button_data);
  
  delay(200);
}
