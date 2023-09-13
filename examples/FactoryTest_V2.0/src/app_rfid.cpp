#include "app_rfid.h"

const uint8_t customAddress = 0x28;

TwoWire &customI2C = Wire;

MFRC522DriverI2C driver{customAddress, customI2C}; // Create I2C driver.

MFRC522 mfrc522{driver}; // Create MFRC522 instance.

uint8_t init_status = 0;

bool init_rfid(void)
{
    bool res = 0;

    if (i2c_check(0x28)) {
        res = mfrc522.PCD_Init();
        delay(5);
        // MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);    
    } else {
        flag_i2c_test_failed = 1;
    }

    if (res) init_status = 1;
    else init_status = 0;

    return res;
}

void ShowReaderDetails(byte *uid, byte *length) 
{
    if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        // return;
    }
    // Serial.print(F("Card UID:"));
    *length = mfrc522.uid.size;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        // Serial.print(mfrc522.uid.uidByte[i], HEX);
        uid[i] = mfrc522.uid.uidByte[i];
    }
    // Serial.println();  
    // MFRC522Debug::PICC_DumpToSerial(mfrc522, Serial, &(mfrc522.uid));
}