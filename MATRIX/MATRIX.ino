#include <M5Stack.h>
#include <FastLED.h>


/***
 *  note:You should first install the Fastled library.
 *  
 ***/

#define DATA_PIN    15
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64
CRGB leds[NUM_LEDS];


#define BRIGHTNESS  5

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setCursor(120, 110, 4);
  M5.Lcd.println("MATRIX");

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 64; i++){
    leds[i] = CRGB::White;
    FastLED.show();
  }
  delay(500);
  // Now turn the LED off, then pause
  for(int i = 0; i < 64; i++){
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  delay(500);

}
