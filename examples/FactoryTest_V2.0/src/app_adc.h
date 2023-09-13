#pragma once

#include "M5Unified.h"
#include "main.h"
#include <ADS1115_WE.h> 

#define ADC_ADDR 0x48

void init_adc_test(void);
float readChannel(ADS1115_MUX channel);