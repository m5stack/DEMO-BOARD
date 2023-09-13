#include "app_step_motor.h"

const int MOTOR_A = 12;
const int MOTOR_B = 15;
const int MOTOR_C = 2;
const int MOTOR_D = 13;

uint8_t step_status = 0;

void init_step_motor(void)
{
    gpio_reset_pin(GPIO_NUM_12);
    gpio_reset_pin(GPIO_NUM_15);
    gpio_reset_pin(GPIO_NUM_2);
    gpio_reset_pin(GPIO_NUM_13);   

    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);
    pinMode(MOTOR_C, OUTPUT);
    pinMode(MOTOR_D, OUTPUT);     
}

void step_motor(void) {
    static uint32_t step_motor_delay = 0;

    if (step_motor_delay < millis()) {
        switch (step_status)
        {
        case 0:
            digitalWrite(MOTOR_A, HIGH);
            digitalWrite(MOTOR_B, HIGH);
            digitalWrite(MOTOR_C, LOW);
            digitalWrite(MOTOR_D, LOW);
            break;
        case 1:
            digitalWrite(MOTOR_A, LOW);
            digitalWrite(MOTOR_B, HIGH);
            digitalWrite(MOTOR_C, HIGH);
            digitalWrite(MOTOR_D, LOW);
            break;
        case 2:
            digitalWrite(MOTOR_A, LOW);
            digitalWrite(MOTOR_B, LOW);
            digitalWrite(MOTOR_C, HIGH);
            digitalWrite(MOTOR_D, HIGH);
            break;
        case 3:
            digitalWrite(MOTOR_A, HIGH);
            digitalWrite(MOTOR_B, LOW);
            digitalWrite(MOTOR_C, LOW);
            digitalWrite(MOTOR_D, HIGH);
            break;
        
        default:
            break;
        }        
        step_status++;
        if (step_status > 3) step_status = 0;
        step_motor_delay = millis() + 2;
    }    
}