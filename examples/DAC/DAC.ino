#include <M5Stack.h>

#define DAC_ADDR 0x4C

void outVoltage(uint8_t ch,uint16_t v){
  
   Wire.beginTransmission(DAC_ADDR);
   Wire.write(0x10|(ch<<1));
   
   Wire.write((v >> 2) & 0xff);
   Wire.write((v << 6) & 0xff);
   Wire.endTransmission();
}

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Wire.begin(21, 22);
  dacWrite(25, 0);

  M5.Lcd.setCursor(140, 0, 4);
  M5.Lcd.print("DAC");

  outVoltage(0,256);   //1.25v
  outVoltage(1,512);   //2.50v
  outVoltage(2,768);   //3.75v
  outVoltage(3,1023);  //5.00v

  M5.Lcd.setCursor(40, 100, 4);
  M5.Lcd.println("ch0:1.25V ch1:2.50V");
  M5.Lcd.setCursor(40, 130, 4);
  M5.Lcd.println("ch2:3.75V ch3:5.00V");
}

void loop() {
  delay(200);
}
