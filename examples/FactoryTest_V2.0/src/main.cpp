#include <Arduino.h>
#include "M5Unified.h"
#include <ADS1115_WE.h> 
#include "main.h"
#include "app_test_page.h"

void setup() {
  M5.begin();

  M5.Display.setEpdMode(epd_mode_t::epd_fastest); // fastest but very-low quality.  
  if (M5.Display.width() < M5.Display.height())
  { /// Landscape mode.
    M5.Display.setRotation(M5.Display.getRotation() ^ 1);
  }
  M5.Display.setFont(&fonts::efontCN_12);
  M5.Display.clear(WHITE);

  M5.Log.setLogLevel(m5::log_target_serial, ESP_LOG_DEBUG);
  M5.Log.setEnableColor(m5::log_target_serial, true);
  M5.Log.setSuffix(m5::log_target_serial, "\n");
  
  M5.Ex_I2C.begin(I2C_PORT, I2C_SDA, I2C_SCL);
  init_dac_test();
}

void loop() {
  switch (page_status)
  {
  case PAGE_DAC:
    page_dac_test();
    break;
  case PAGE_ADC:
    page_adc_test();
    break;
  case PAGE_RFID:
    page_rfid_test();
    break;
  case PAGE_TEMP:
    page_temp_test();
    break;
  case PAGE_AIR_PRESSURE:
    page_pressure_test();
    break;
  case PAGE_LUMINOSITY:
    page_luminosity_test();
    break;
  case PAGE_MICROPHONE:
    page_microphone_test();
    break;
  case PAGE_RS485:
    page_rs485_test();
    break;
  case PAGE_RS232:
    page_rs232_test();
    break;
  case PAGE_RELAY:
    page_relay_test();
    break;
  case PAGE_RGB:
    page_rgb_test();
    break;
  case PAGE_SERVO:
    page_servo_test();
    break;
  case PAGE_JOYSTICK:
    page_joystick_test();
    break;
  case PAGE_ENCODER:
    page_encoder_test();
    break;
  case PAGE_DC_MOTOR:
    page_dcmotor_test();
    break;
  case PAGE_STEP_MOTOR:
    page_stepmotor_test();
    break;
  case PAGE_KEYBOARD:
    page_keyboard_test();
    break;
  
  default:
    break;
  }
}

bool i2c_check(uint8_t addr)
{
  m5gfx::i2c::beginTransaction(I2C_PORT, addr, 100000); 
  if (m5gfx::i2c::endTransaction(I2C_PORT).error() == 0)
  {
    return true;
  }
  else {
    return false;
  }
}
