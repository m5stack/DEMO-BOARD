/*
    Name:       DC-Motor.ino
    Created:    2019/5/17 10:06:15
    Author:     shaoxiang
*/

#include <M5Stack.h>
// The setup() function runs once each time the micro-controller starts
void setup() {
  // init lcd, serial, but don't init sd card
  M5.begin();
  M5.Lcd.setCursor(120,0,4);
  M5.Lcd.println("DC-motor");
  M5.Lcd.setCursor(30, 200);
  M5.Lcd.println("Forward");
  M5.Lcd.setCursor(140, 200);
  M5.Lcd.println("Stop");
  M5.Lcd.setCursor(220, 200);
  M5.Lcd.println("Reverse");
  
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(13, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
}

// Add the main program code into the continuous loop() function
void loop() {
  M5.update();
 
  if (M5.BtnA.wasReleased()) {
    digitalWrite(22, LOW);
    digitalWrite(21, HIGH);
  } else if (M5.BtnB.wasReleased()) {
    digitalWrite(21, LOW);
    digitalWrite(22, LOW);
  } else if (M5.BtnC.wasReleased()) {
    digitalWrite(21, LOW);
    digitalWrite(22, HIGH);
  } 
}
