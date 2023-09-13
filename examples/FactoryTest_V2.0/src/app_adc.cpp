#include "app_adc.h"

ADS1115_WE adc = ADS1115_WE(ADC_ADDR);

float readChannel(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc.setCompareChannels(channel);
  voltage = adc.getResult_V(); // alternative: getResult_mV for Millivolt
  return voltage;
}

void init_adc_test(void)
{
  if(!adc.init()){
    Serial.println("ADS1115 not connected!");
    flag_i2c_test_failed = 1;
  }
  else {
    adc.setVoltageRange_mV(ADS1115_RANGE_6144);
    adc.setCompareChannels(ADS1115_COMP_0_GND);
    adc.setMeasureMode(ADS1115_CONTINUOUS);      
  } 
}