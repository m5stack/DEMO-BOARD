#include <M5Stack.h>

const int Analog = 35;
const int Digtal = 2;
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  pinMode(Digtal, INPUT_PULLUP);
  dacWrite(25, 0);

  M5.Lcd.setCursor(100, 0, 4);
  M5.Lcd.print("LUMINOSITY");

}
uint16_t a_data;
uint16_t d_data;

void loop() {
  // put your main code here, to run repeatedly:
  a_data = analogRead(Analog);
  d_data = digitalRead(Digtal);

  Serial.printf("Analog:%0d Digtal:%0d\n", a_data, d_data);

  M5.Lcd.setCursor(30, 120, 4);
  M5.Lcd.printf("Analog:%0d Digtal:%0d\n", a_data, d_data);
  
  delay(200);

}
