#pragma once

#include "M5Unified.h"
#include "main.h"
#include "app_dac.h"
#include "app_adc.h"
#include "app_rfid.h"
#include "app_env.h"
#include "app_luminosity.h"
#include "app_microphone.h"
#include "app_rs485.h"
#include "app_rs232.h"
#include "app_relay.h"
#include "app_rgb.h"
#include "app_servo.h"
#include "app_joystick.h"
#include "app_encoder.h"
#include "app_dc_motor.h"
#include "app_step_motor.h"
#include "app_keyboard.h"

extern uint8_t page_status;

enum {PAGE_DAC = 0, 
PAGE_ADC, 
PAGE_RFID, 
PAGE_TEMP, 
PAGE_AIR_PRESSURE, 
PAGE_LUMINOSITY, 
PAGE_MICROPHONE, 
PAGE_RS485, 
PAGE_RS232, 
PAGE_RELAY, 
PAGE_RGB, 
PAGE_SERVO, 
PAGE_JOYSTICK, 
PAGE_ENCODER, 
PAGE_DC_MOTOR, 
PAGE_STEP_MOTOR, 
PAGE_KEYBOARD};

void page_dac_test(void);
void page_adc_test(void);
void page_rfid_test(void);
void page_temp_test(void);
void page_pressure_test(void);
void page_luminosity_test(void);
void page_microphone_test(void);
void page_rs485_test(void);
void page_rs232_test(void);
void page_relay_test(void);
void page_rgb_test(void);
void page_servo_test(void);
void page_joystick_test(void);
void page_encoder_test(void);
void page_dcmotor_test(void);
void page_stepmotor_test(void);
void page_keyboard_test(void);