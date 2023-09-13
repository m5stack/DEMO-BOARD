#include "app_rgb.h"

#define DATA_PIN 13
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 5

static int led_count = 0;

void init_rgb(void)
{
    gpio_reset_pin(GPIO_NUM_13);
    pinMode(DATA_PIN, OUTPUT);
    digitalWrite(DATA_PIN, LOW);    
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    led_count = 0;
}

void matrix(void) {
    led_count++;
    if (led_count > 400) led_count = 0;
    if ((led_count / 100) == 0) {
        for (int i = 0; i < 64; i++) leds[i] = CRGB::Red;
        leds[0] = CRGB::Red;
        FastLED.show();
    }

    if ((led_count / 100) == 1) {
        for (int i = 0; i < 64; i++) leds[i] = CRGB::Green;
        leds[0] = CRGB::Green;
        FastLED.show();
    }
    if ((led_count / 100) == 2) {
        for (int i = 0; i < 64; i++) leds[i] = CRGB::Blue;
        leds[0] = CRGB::Blue;
        FastLED.show();
    }
}
