#include "app_dac.h"

static void outVoltage(uint8_t ch, uint16_t v) {
  uint8_t tx_data[2] = {0};

  tx_data[0] = ((v >> 2) & 0xff);
  tx_data[1] = ((v << 6) & 0xff);
  M5.Ex_I2C.writeRegister(DAC_ADDR, 0x10 | (ch << 1), tx_data, 2, 100000U);
}

void init_dac_test(void)
{
  if (i2c_check(DAC_ADDR)) {
    outVoltage(0, 256);  // 1.25V
    outVoltage(1, 512);  // 2.50V
    outVoltage(2, 768);  // 3.75V
    outVoltage(3, 1023); // 5.00V      
  } else {
    flag_i2c_test_failed = 1;
  }
}