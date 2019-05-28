#include<M5Stack.h>
#include <Keypad.h>


//https://github.com/Chris--A/Keypad

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns


byte rowPins[ROWS] = {17,16,21,22};
byte colPins[COLS] = {5, 26, 13, 15};

char keys[ROWS][COLS] = {
  {'a','b','c','d'},
  {'e','f','g','h'},
  {'i','j','k','l'},
  {'m','n','o','p'}
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  M5.begin();
}

void loop() {
  //put your main code here, to run repeatedly:
  char key = keypad.getKey();
  if(key){
    Serial.println(key);
  }

}
