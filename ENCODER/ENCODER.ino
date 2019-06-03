#include <M5Stack.h>

const int phaseA = 2;
const int phaseB = 13;
const int Button = 15;

#define GET_CODE() uint8_t(digitalRead(phaseA) << 4 | digitalRead(phaseB))

int32_t count = 65536;
int32_t count_last = 65536;
int32_t count_change = 0;
uint8_t code = 0;
uint8_t code_old = 0;

void encoderEvent() {
  code = GET_CODE();
  if(code != code_old) {
    if(code == 0x00) {
      count_last = count;
      if(code_old == 0x10) {
        count--;
        count_change == -65536 ? count_change : count_change--;
      } else {
        count_change == 65536 ? count_change : count_change++;
      }
    }
    code_old = code;
  }
}

void setup() {
  //put your setup code here, to run once:
  M5.begin();
  pinMode(phaseA, INPUT_PULLUP);
  pinMode(phaseB, INPUT_PULLUP);
  pinMode(Button, INPUT_PULLUP);
  dacWrite(25, 0);

  M5.Lcd.setCursor(100, 0, 4);
  M5.Lcd.print("ENCODER");

  code = GET_CODE();
  code_old = code;

}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t value = digitalRead(Button);
  encoderEvent();
  Serial.printf("code = %d,button = %d\r\n ",count_change,value);

  M5.Lcd.setCursor(30, 120, 4);
  M5.Lcd.printf("code = %05d,button = %d\r\n ",count_change,value);
  delay(1);

}
