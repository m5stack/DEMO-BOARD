#pragma once

#include "main.h"
// #include <WEMOS_SHT3X.h>
#include "M5_ENV.h"

void get_sht30_info(float *temp, float *hum, uint32_t delay_time);
void get_qmp6988_info(float *pres);
void init_qmp6988(void);