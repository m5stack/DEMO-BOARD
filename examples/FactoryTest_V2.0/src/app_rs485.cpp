#include "app_rs485.h"

static int rx_count = 0;
static int rx_num = 0;

void init_rs485(void)
{
    rx_count = 0;
    rx_num = 0;
    Serial1.begin(115200, SERIAL_8N1, 22, 21);
    Serial2.begin(115200, SERIAL_8N1, 16, 17);
}

int16_t uart485(void) {
    Serial2.write('a');
    // rx_count++;
    // if (rx_count > 200) rx_count = 0;
    // if (rx_count == 10) Serial2.write('a');

    if (Serial1.available()) {    // TX,RX有数据
        int ch = Serial1.read();  //读取RS485的数据
        // Serial.write(ch);
        if (ch == 'a') {
            rx_num++;
        }
    }

    return rx_num;
}