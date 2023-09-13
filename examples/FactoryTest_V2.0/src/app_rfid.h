#pragma once

#include "main.h"
#include <MFRC522v2.h>
#include <MFRC522DriverI2C.h>
#include <MFRC522Debug.h>

extern uint8_t init_status;

bool init_rfid(void);
void ShowReaderDetails(byte *uid, byte *length);
// void rfid_dump_info(void);