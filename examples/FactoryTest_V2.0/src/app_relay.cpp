#include "app_relay.h"

const int In_0  = 13;

void init_relay(void) 
{
    gpio_reset_pin(GPIO_NUM_13);
    pinMode(In_0, OUTPUT);
    digitalWrite(In_0, HIGH);
}
