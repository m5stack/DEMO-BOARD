#include "app_env.h"

SHT3X sht30;
QMP6988 qmp6988;

void get_sht30_info(float *temp, float *hum, uint32_t delay_time) {
    static uint32_t get_delay_millis = 0;

    if (get_delay_millis < millis()) {
        get_delay_millis = millis() + delay_time;
        if(sht30.get()==0){
            Serial.print("Temperature in Celsius : ");
            Serial.println(sht30.cTemp);
            *temp = sht30.cTemp;
            Serial.print("Temperature in Fahrenheit : ");
            Serial.println(sht30.fTemp);
            Serial.print("Relative Humidity : ");
            Serial.println(sht30.humidity);
            *hum = sht30.humidity;
            Serial.println();
        }
        else
        {
            Serial.println("Error!");
        }        
    }
}

void init_qmp6988(void)
{
    if (i2c_check(0x70))
        qmp6988.init(0x70, &Wire);
}

void get_qmp6988_info(float *pres) {
    static uint32_t get_qmp_delay_time;
    float pressure = 0.0;
    
    if (get_qmp_delay_time < millis()) {
        get_qmp_delay_time = millis() + 50;
        pressure = qmp6988.calcPressure();

        *pres = pressure;
        Serial.printf("Pressure:%2.0fPa\r\n", pressure);        
    }
}