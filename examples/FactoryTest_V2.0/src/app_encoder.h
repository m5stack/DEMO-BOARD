#pragma once

#include "main.h"
#include "AiEsp32RotaryEncoder.h"

void init_encoder(bool with_button);
void get_encoder(uint32_t *encoder, uint8_t *button, bool with_button);