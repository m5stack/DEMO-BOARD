#include "app_dc_motor.h"

#define MOTOR_P 12 
#define MOTOR_N 15

uint8_t dc_direct_flag = 0;

void init_dc_motor(void)
{
    gpio_reset_pin(GPIO_NUM_12);
    gpio_reset_pin(GPIO_NUM_15);    
    pinMode(MOTOR_P, OUTPUT);
    pinMode(MOTOR_N, OUTPUT);    
}

void dcmotor(void)
{
    static uint32_t dc_count = 0;

    if (dc_count < millis()) {
        dc_count = millis() + 3000;
        if (dc_direct_flag) {
            dc_direct_flag = 0;
        } else {
            dc_direct_flag = 1;
        }
    }
    if (dc_direct_flag) {
        Serial.println("forwardforward");
        digitalWrite(MOTOR_P, HIGH);
        digitalWrite(MOTOR_N, LOW);
    } else {
        Serial.println("backback");
        digitalWrite(MOTOR_P, LOW);
        digitalWrite(MOTOR_N, HIGH);        
    }
}
