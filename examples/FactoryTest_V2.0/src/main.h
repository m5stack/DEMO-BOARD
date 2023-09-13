#pragma once

#include <Arduino.h>
#include "M5Unified.h"

#define I2C_PORT I2C_NUM_0
#define I2C_SDA 21
#define I2C_SCL 22

extern uint8_t flag_i2c_test_failed;

const int Analog = 35;
const int Digtal = 2;

bool i2c_check(uint8_t addr);