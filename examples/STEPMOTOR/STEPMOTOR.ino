#include <M5Stack.h>

const int MOTOR_A = 2;
const int MOTOR_B = 5;
const int MOTOR_C = 12;
const int MOTOR_D = 13;
void setup() {
  M5.begin();
   // put your setup code here, to run once:
  M5.Lcd.setCursor(80,110,4);
  M5.Lcd.println("STEPMOTOR");
  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);
  pinMode(MOTOR_C, OUTPUT);
  pinMode(MOTOR_D, OUTPUT); 
}
void loop() {
  
  digitalWrite(MOTOR_A, HIGH);
  digitalWrite(MOTOR_B, HIGH);
  digitalWrite(MOTOR_C, LOW);
  digitalWrite(MOTOR_D, LOW);
  delay(2);
  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, HIGH);
  digitalWrite(MOTOR_C, HIGH);
  digitalWrite(MOTOR_D, LOW);
  delay(2);
  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, LOW);
  digitalWrite(MOTOR_C, HIGH);
  digitalWrite(MOTOR_D, HIGH);
  delay(2);
  digitalWrite(MOTOR_A, HIGH);
  digitalWrite(MOTOR_B, LOW);
  digitalWrite(MOTOR_C, LOW);
  digitalWrite(MOTOR_D, HIGH);
  delay(2);
}
