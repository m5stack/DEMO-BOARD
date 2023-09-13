#include "app_joystick.h"

void init_joystick(void)
{
    gpio_reset_pin(GPIO_NUM_2);
    gpio_reset_pin(GPIO_NUM_13);
    gpio_reset_pin(GPIO_NUM_15);
    pinMode(2, INPUT_PULLUP);    
    pinMode(13, INPUT_PULLUP);    
    pinMode(15, INPUT_PULLUP);    
}

void joystick(uint16_t *x, uint16_t *y, uint8_t *btn)
{
    uint16_t x_data     = 0;
    uint16_t y_data     = 0;
    uint8_t button_data = 0;
    static uint32_t joystick_delay_time = 0;

    if (joystick_delay_time < millis()) {
        x_data      = analogRead(2);
        y_data      = analogRead(13);
        button_data = digitalRead(15);    
        Serial.printf("x:%0d y:%0d button:%d\n", x_data, y_data, button_data);     
        *x = x_data;
        *y = y_data;
        *btn = button_data;   
        joystick_delay_time = millis() + 200;
    }
}