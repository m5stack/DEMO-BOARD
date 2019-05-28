#include <M5Stack.h>


const int In_0 = 23;
const int In_1 = 19;
const int In_2 = 18;
const int In_3 = 2;
const int In_4 = 5;
const int In_5 = 12;
const int In_6 = 13;
const int In_7 = 15;

void setup() {
  // put your setup code here, to run once:

  pinMode(In_0,OUTPUT);
  pinMode(In_1,OUTPUT);
  pinMode(In_2,OUTPUT);
  pinMode(In_3,OUTPUT);
  pinMode(In_4,OUTPUT);
  pinMode(In_5,OUTPUT);
  pinMode(In_6,OUTPUT);
  pinMode(In_7,OUTPUT);


  digitalWrite(In_0, LOW);
  digitalWrite(In_1, LOW);
  digitalWrite(In_2, LOW);
  digitalWrite(In_3, LOW);
  digitalWrite(In_4, LOW);
  digitalWrite(In_5, LOW);
  digitalWrite(In_6, LOW);
  digitalWrite(In_7, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(In_0, LOW);
  digitalWrite(In_1, LOW);
  digitalWrite(In_2, LOW);
  digitalWrite(In_3, LOW);
  digitalWrite(In_4, LOW);
  digitalWrite(In_5, LOW);
  digitalWrite(In_6, LOW);
  digitalWrite(In_7, LOW);


  delay(3000);



  digitalWrite(In_0, HIGH);
  digitalWrite(In_1, HIGH);
  digitalWrite(In_2, HIGH);
  digitalWrite(In_3, HIGH);
  digitalWrite(In_4, HIGH);
  digitalWrite(In_5, HIGH);
  digitalWrite(In_6, HIGH);
  digitalWrite(In_7, HIGH);


  delay(3000);

}
