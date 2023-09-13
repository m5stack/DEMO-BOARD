#include "app_rs232.h"

static int rs232_rx_count = 0;
static int rs232_rx_num = 0;

void init_rs232(void)
{
    rs232_rx_count = 0;
    rs232_rx_num = 0;
    Serial2.begin(115200, SERIAL_8N1, 16, 17);
}

int16_t uart232(void) {

    Serial2.write('a');
    if (Serial2.available()) {
        int ch = Serial2.read();
        // Serial.write(ch);
        if (ch == 'a') {
            rs232_rx_num++;
        }
    }
    // rs232_rx_count++;
    // if (rs232_rx_count > 6000) rs232_rx_count = 0;
    // if (rs232_rx_count == 10) Serial2.write('a');

    return rs232_rx_num;
}