#include "app_keyboard.h"

const uint8_t ROWS = 4;  // four rows
const uint8_t COLS = 4;  // three columns

uint8_t rowPins[ROWS] = {5, 12, 13, 15};
uint8_t colPins[COLS] = {17, 16, 21, 22};

char keys[ROWS*COLS] = {'a', 'b', 'c', 'd',
                         'e', 'f', 'g', 'h',
                         'i', 'j', 'k', 'l',
                         'm', 'n', 'o', 'p'};

void init_keyboard(void)
{
    gpio_reset_pin(GPIO_NUM_17);
    gpio_reset_pin(GPIO_NUM_16);
    gpio_reset_pin(GPIO_NUM_21);
    gpio_reset_pin(GPIO_NUM_22);
    gpio_reset_pin(GPIO_NUM_5);
    gpio_reset_pin(GPIO_NUM_26);
    gpio_reset_pin(GPIO_NUM_13);
    gpio_reset_pin(GPIO_NUM_15);

    for (int i = 0; i < 4; i++)
    {
        pinMode(rowPins[i], INPUT_PULLUP);
        pinMode(colPins[i], OUTPUT);
    }

}

char keyboard(void) {
    uint8_t key_index = 0;
    char key_value = 0;

    digitalWrite(colPins[0], LOW);  
    digitalWrite(colPins[1], LOW);  
    digitalWrite(colPins[2], LOW);  
    digitalWrite(colPins[3], LOW);  

    if (!digitalRead(rowPins[0]) || !digitalRead(rowPins[1]) || 
    !digitalRead(rowPins[2]) || !digitalRead(rowPins[3]))
    {
        delay(100);
        if (!digitalRead(rowPins[0]) || !digitalRead(rowPins[1]) || 
        !digitalRead(rowPins[2]) || !digitalRead(rowPins[3]))
        {
            digitalWrite(colPins[0], LOW);  
            digitalWrite(colPins[1], HIGH);  
            digitalWrite(colPins[2], HIGH);  
            digitalWrite(colPins[3], HIGH); 
            for (int j = 0; j < 4; j++)
            {
                if (!digitalRead(rowPins[j]))
                {
                    key_index = 0 + j * 4;
                    key_value = keys[key_index];
                    Serial.println(key_value);
                    // Serial.println(0 + j * 4 + 1);//在串口监视器中输出键盘编号
                    while (!digitalRead(rowPins[j]));
                }
            }
            digitalWrite(colPins[0], HIGH);  
            digitalWrite(colPins[1], LOW);  
            digitalWrite(colPins[2], HIGH);  
            digitalWrite(colPins[3], HIGH); 
            for (int j = 0; j < 4; j++)
            {
                if (!digitalRead(rowPins[j]))
                {
                    key_index = 1 + j * 4;
                    key_value = keys[key_index];
                    Serial.println(key_value);                 
                    // Serial.println(1 + j * 4 + 1);
                    while (!digitalRead(rowPins[j]));
                }
            }
            digitalWrite(colPins[0], HIGH);  
            digitalWrite(colPins[1], HIGH);  
            digitalWrite(colPins[2], LOW);  
            digitalWrite(colPins[3], HIGH); 
            for (int j = 0; j < 4; j++)
            {
                if (!digitalRead(rowPins[j]))
                {
                    key_index = 2 + j * 4;
                    key_value = keys[key_index];
                    Serial.println(key_value);                    
                    // Serial.println(2 + j * 4 + 1);
                    while (!digitalRead(rowPins[j]));
                }
            }
            digitalWrite(colPins[0], HIGH);  
            digitalWrite(colPins[1], HIGH);  
            digitalWrite(colPins[2], HIGH);  
            digitalWrite(colPins[3], LOW); 
            for (int j = 0; j < 4; j++)
            {
                if (!digitalRead(rowPins[j]))
                {
                    key_index = 3 + j * 4;
                    key_value = keys[key_index];
                    Serial.println(key_value);                   
                    // Serial.println(3 + j * 4 + 1);
                    while (!digitalRead(rowPins[j]));
                }
            }
        }
    }

    return key_value;    
}