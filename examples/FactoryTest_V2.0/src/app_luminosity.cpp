
#include "app_luminosity.h"

void luminosity(uint16_t *analog_data, uint16_t *digital_data) {
    static uint32_t lumi_delay_time = 0;

    if (lumi_delay_time < millis()) {
        *analog_data = analogRead(Analog);
        *digital_data = digitalRead(Digtal);

        Serial.printf("Analog:%0d Digtal:%0d\n", *analog_data, *digital_data);        
        lumi_delay_time = millis() + 50;
    }
}