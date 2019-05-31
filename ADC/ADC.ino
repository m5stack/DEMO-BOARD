#include <M5Stack.h>

/*
  note:
*/
#define ADC_ADDR 0x48

uint16_t outVoltage(uint8_t ch){

  uint8_t  data_L = 0;
  uint8_t  data_H = 0;
  uint16_t data_adc = 0;
  
  Wire.beginTransmission(ADC_ADDR);
  Wire.write(0X01);
  Wire.write(0XC0 | (ch << 4));
  //Wire.write(0XC4);   
  Wire.write(0X83);
  Wire.endTransmission();

  Wire.beginTransmission(ADC_ADDR);
  Wire.write(0x00); 
  Wire.endTransmission();

  delay(50);
  
  Wire.requestFrom(ADC_ADDR, 2);
  while(Wire.available()){
    data_H = Wire.read();
    data_L = Wire.read();
  }
  
  data_adc = (data_H << 8) | data_L;
  return data_adc;
}
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Wire.begin();
  dacWrite(25, 0);

  M5.Lcd.setCursor(140, 0, 4);
  M5.Lcd.print("ADC");

}
uint16_t adc_ch0 = 0;
uint16_t adc_ch1 = 0;
uint16_t adc_ch2 = 0;
uint16_t adc_ch3 = 0;
void loop() {
  adc_ch0 = outVoltage(0);
  adc_ch1 = outVoltage(1);
  adc_ch2 = outVoltage(2);
  adc_ch3 = outVoltage(3);
  Serial.printf("ch0:%d ch1:%d ch2:%d  ch3:%d\n", adc_ch0, adc_ch1, adc_ch2,adc_ch3);
  delay(500);
}
