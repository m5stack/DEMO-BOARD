#include "app_encoder.h"

#define ROTARY_ENCODER_A_PIN 13
#define ROTARY_ENCODER_B_PIN 2
#define ROTARY_ENCODER_BUTTON_PIN 15
#define ROTARY_ENCODER_NO_PIN -1

#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 2

static uint8_t button_value = 0;
static uint32_t encoder_value = 0;

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, 
ROTARY_ENCODER_NO_PIN, 
ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

static void rotary_onButtonClick()
{
	static unsigned long lastTimePressed = 0;
	//ignore multiple press in that time milliseconds
	if (millis() - lastTimePressed < 500)
	{
		return;
	}
	lastTimePressed = millis();
	Serial.print("button pressed ");
	Serial.print(millis());
	Serial.println(" milliseconds after restart");
}

static void rotary_loop(uint32_t *encoder, uint8_t *button, bool with_button)
{
    static uint8_t button_data;
	//dont print anything unless value changed
	if (rotaryEncoder.encoderChanged())
	{
        encoder_value = rotaryEncoder.readEncoder();
		Serial.print("Value: ");
		Serial.println(encoder_value);
        *encoder = encoder_value;
	}
	if (with_button) {
		button_data = digitalRead(ROTARY_ENCODER_BUTTON_PIN); 
		*button = button_data;
		if (rotaryEncoder.isEncoderButtonClicked())
		{
			rotary_onButtonClick();
		}
	}
}

void IRAM_ATTR readEncoderISR()
{
	rotaryEncoder.readEncoder_ISR();
}

void init_encoder(bool with_button)
{
    gpio_reset_pin(GPIO_NUM_2);
    gpio_reset_pin(GPIO_NUM_13);
	if (with_button) {
		gpio_reset_pin(GPIO_NUM_15);   
		pinMode(ROTARY_ENCODER_BUTTON_PIN, INPUT_PULLUP);
	}
	rotaryEncoder.begin();
	rotaryEncoder.setup(readEncoderISR);
	bool circleValues = false;
	rotaryEncoder.setBoundaries(-65536, 65536, circleValues);
    rotaryEncoder.setAcceleration(1);    
}

void get_encoder(uint32_t *encoder, uint8_t *button, bool with_button)
{
    static uint32_t encoder_delay = 0;

    if (encoder_delay < millis()) {
        rotary_loop(encoder, button, with_button);
        encoder_delay = millis() + 50;
    }    
}

