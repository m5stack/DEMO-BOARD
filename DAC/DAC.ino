#include <M5Stack.h>

/*
  note:
*/
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
}

void loop() {
  delay(200);
}
