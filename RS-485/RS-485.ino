#include <M5Stack.h>

void setup() {
  // put your setup code here, to run once:
  M5.begin();

  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  M5.Lcd.setCursor(100, 0, 4);
  M5.Lcd.print("RS-485");

}
int rx_num = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial2.available()) {
    int ch = Serial2.read();
    Serial.write(ch);
    if(ch == 'a'){
      rx_num++;
    }
    M5.Lcd.setCursor(30, 120, 4);
    M5.Lcd.printf("rx_num = %d\n", rx_num);
  }
  delay(500);
  Serial2.write('a');


}
