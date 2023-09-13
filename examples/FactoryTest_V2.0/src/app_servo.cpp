#include "app_servo.h"

#define SERVO_PIN 13
int servo_count = 0;
int freq        = 50;
int ledChannel  = 0;
int resolution  = 8;

void init_servo(void)
{
    gpio_reset_pin(GPIO_NUM_13);
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(SERVO_PIN, ledChannel);
    servo_count = 0;    
}

void servo(void)
{
    servo_count++;
    if (servo_count > 3000) servo_count = 0;
    if ((servo_count / 1000) == 0) {
        ledcWrite(ledChannel, 6);  // 0°
    }
    if ((servo_count / 1000) == 1) {
        ledcWrite(ledChannel, 18);  // 0°
    }

    if ((servo_count / 1000) == 2) {
        ledcWrite(ledChannel, 30);  // 0°
    }
}