#include <M5Stack.h>
#include <Keypad.h>
#include <FastLED.h>
#include <driver/ledc.h>
#include "MFRC522_I2C.h"
#include "M5_ENV.h"

int count_flag     = 0;
uint8_t setup_flag = 0;

void joystick(void) {
    // put your main code here, to run repeatedly:
    uint16_t x_data     = 0;
    uint16_t y_data     = 0;
    uint8_t button_data = 0;

    M5.Lcd.setCursor(100, 30, 4);
    M5.Lcd.println("JOYSTICK");
    M5.Lcd.setCursor(0, 60, 4);
    M5.Lcd.println("PIN : x_adc:35,y_adc:36,button:2");

    if (!setup_flag) {
        setup_flag = 1;
        gpio_reset_pin(GPIO_NUM_2);
        gpio_reset_pin(GPIO_NUM_35);
        gpio_reset_pin(GPIO_NUM_36);
        pinMode(2, INPUT_PULLUP);
    }
    x_data      = analogRead(35);
    y_data      = analogRead(36);
    button_data = digitalRead(2);

    Serial.printf("x:%0d y:%0d button:%d\n", x_data, y_data, button_data);

    M5.Lcd.setCursor(30, 120, 4);
    M5.Lcd.printf("x:%04d y:%04d button:%d\n", x_data, y_data, button_data);

    delay(200);
}

#define DAC_ADDR 0x4C

void outVoltage(uint8_t ch, uint16_t v) {
    Wire.beginTransmission(DAC_ADDR);
    Wire.write(0x10 | (ch << 1));

    Wire.write((v >> 2) & 0xff);
    Wire.write((v << 6) & 0xff);
    Wire.endTransmission();
}
void dac() {
    if (!setup_flag) {
        setup_flag = 1;
        gpio_reset_pin(GPIO_NUM_21);
        gpio_reset_pin(GPIO_NUM_22);
        Wire.begin();

        M5.Lcd.setCursor(140, 30, 4);
        M5.Lcd.print("DAC");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN : SCL:22,SDA:21");

        outVoltage(0, 256);   // 1.25v
        outVoltage(1, 512);   // 2.50v
        outVoltage(2, 768);   // 3.75v
        outVoltage(3, 1023);  // 5.00v
    }
    outVoltage(0, 256);   // 1.25v
    outVoltage(1, 512);   // 2.50v
    outVoltage(2, 768);   // 3.75v
    outVoltage(3, 1023);  // 5.00v
}

#define ADC_ADDR 0x48

uint16_t InVoltage(uint8_t ch) {
    uint8_t data_L    = 0;
    uint8_t data_H    = 0;
    uint16_t data_adc = 0;

    Wire.beginTransmission(ADC_ADDR);
    Wire.write(0X01);
    Wire.write(0XC0 | (ch << 4));
    Wire.write(0X83);
    Wire.endTransmission();

    Wire.beginTransmission(ADC_ADDR);
    Wire.write(0x00);
    Wire.endTransmission();

    delay(50);

    Wire.requestFrom(ADC_ADDR, 2);
    while (Wire.available()) {
        data_H = Wire.read();
        data_L = Wire.read();
    }

    data_adc = (data_H << 8) | data_L;
    return data_adc;
}

void adc() {
    uint16_t adc_ch0 = 0;
    uint16_t adc_ch1 = 0;
    uint16_t adc_ch2 = 0;
    uint16_t adc_ch3 = 0;

    if (!setup_flag) {
        setup_flag = 1;
        gpio_reset_pin(GPIO_NUM_21);
        gpio_reset_pin(GPIO_NUM_22);
        Wire.begin();

        M5.Lcd.setCursor(140, 30, 4);
        M5.Lcd.print("ADC");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN : SCL:22,SDA:21");
    }
    adc_ch0 = InVoltage(0);
    adc_ch1 = InVoltage(1);
    adc_ch2 = InVoltage(2);
    adc_ch3 = InVoltage(3);
    Serial.printf("ch0:%d ch1:%d ch2:%d  ch3:%d\n", adc_ch0, adc_ch1, adc_ch2,
                  adc_ch3);

    M5.Lcd.setCursor(0, 120, 4);
    M5.Lcd.printf("ch0:%05d ch1:%05d\n", adc_ch0, adc_ch1);
    M5.Lcd.printf("ch2:%05d ch3:%05d\n", adc_ch2, adc_ch3);
    // delay(500);
}

const int phaseA = 2;
const int phaseB = 13;
const int Button = 15;
#define GET_CODE() uint8_t(digitalRead(phaseA) << 4 | digitalRead(phaseB))

int32_t count        = 65536;
int32_t count_last   = 65536;
int32_t count_change = 0;
uint8_t code         = 0;
uint8_t code_old     = 0;
void encoderEvent() {
    code = GET_CODE();
    if (code != code_old) {
        if (code == 0x00) {
            count_last = count;
            if (code_old == 0x10) {
                count--;
                count_change == -65536 ? count_change : count_change--;
            } else {
                count_change == 65536 ? count_change : count_change++;
            }
        }
        code_old = code;
    }
}

void encoder() {
    if (!setup_flag) {
        setup_flag = 1;
        gpio_reset_pin(GPIO_NUM_2);
        gpio_reset_pin(GPIO_NUM_13);
        gpio_reset_pin(GPIO_NUM_15);
        pinMode(phaseA, INPUT_PULLUP);
        pinMode(phaseB, INPUT_PULLUP);
        pinMode(Button, INPUT_PULLUP);
        // M5.Lcd.setCursor(100, 0, 4);
        // M5.Lcd.print("ENCODER");

        M5.Lcd.setCursor(100, 30, 4);
        M5.Lcd.println("ENCODER");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN : a:2,b:13,button:15");

        code     = GET_CODE();
        code_old = code;
    }

    uint8_t value = digitalRead(Button);
    encoderEvent();
    Serial.printf("code = %d,button = %d\r\n ", count_change, value);

    M5.Lcd.setCursor(30, 120, 4);
    M5.Lcd.printf("code = %05d,button = %d\r\n ", count_change, value);
    delay(1);
}

const byte ROWS = 4;  // four rows
const byte COLS = 4;  // three columns

byte rowPins[ROWS] = {17, 16, 21, 22};
byte colPins[COLS] = {5, 26, 13, 15};

char keys[ROWS][COLS] = {{'a', 'b', 'c', 'd'},
                         {'e', 'f', 'g', 'h'},
                         {'i', 'j', 'k', 'l'},
                         {'m', 'n', 'o', 'p'}};
Keypad keypad         = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
// Keypad keypad;
void key() {
    if (!setup_flag) {
        setup_flag = 1;
        // Wire.end();

        // Wire.end();
        // pinMode(21,INPUT_PULLUP);
        // pinMode(22,INPUT_PULLUP);
        gpio_reset_pin(GPIO_NUM_17);
        gpio_reset_pin(GPIO_NUM_16);
        gpio_reset_pin(GPIO_NUM_21);
        gpio_reset_pin(GPIO_NUM_22);
        gpio_reset_pin(GPIO_NUM_5);
        gpio_reset_pin(GPIO_NUM_26);
        gpio_reset_pin(GPIO_NUM_13);
        gpio_reset_pin(GPIO_NUM_15);

        M5.Lcd.setCursor(100, 30, 4);
        M5.Lcd.println("KEYBOARD");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN : r0:17,r1:16,r2:21,r3:22");
        M5.Lcd.println("PIN : c0: 5,c1:26,c2:13,c3:15");
        keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
    }

    char key = keypad.getKey();
    if (key) {
        Serial.println(key);
        M5.Lcd.fillRect(150, 150, 80, 50, BLACK);
        M5.Lcd.setCursor(150, 140, 4);
        M5.Lcd.printf("%c", key);
    }
}

#define DATA_PIN 15
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 5

int led_count = 0;
void matrix() {
    if (!setup_flag) {
        setup_flag = 1;

        gpio_reset_pin(GPIO_NUM_15);

        M5.Lcd.setCursor(100, 30, 4);
        M5.Lcd.println("MATRIX");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN : SIGNAL:15");

        // FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds,
        // NUM_LEDS).setCorrection(TypicalLEDStrip);
        // FastLED.addLeds<NEOPIXEL,DATA_PIN,COLOR_ORDER>(leds,
        // NUM_LEDS).setCorrection(TypicalLEDStrip);
        FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
        // NEOPIXEL
        FastLED.setBrightness(BRIGHTNESS);
        led_count = 0;
    }
    led_count++;
    if (led_count > 2000) led_count = 0;
    if ((led_count / 500) == 0) {
        for (int i = 0; i < 64; i++) leds[i] = CRGB::Red;
        FastLED.show();
    }

    if ((led_count / 500) == 1) {
        for (int i = 0; i < 64; i++) leds[i] = CRGB::Green;
        FastLED.show();
    }
    if ((led_count / 500) == 2) {
        for (int i = 0; i < 64; i++) leds[i] = CRGB::Blue;
        FastLED.show();
    }
}

int dc_count = 0;
void dcmotor() {
    if (!setup_flag) {
        setup_flag = 1;

        M5.Lcd.setCursor(100, 30, 4);
        M5.Lcd.println("DC-MOTOR");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN : M+:13,M-:15,ea:21,eb:22");

        pinMode(13, OUTPUT);
        pinMode(15, OUTPUT);
        pinMode(21, INPUT_PULLUP);
        pinMode(22, INPUT_PULLUP);
        dc_count = 0;
    }

    dc_count++;
    if (dc_count > 4000) dc_count = 0;

    digitalWrite(13, LOW);
    digitalWrite(15, HIGH);
}
const int In_0  = 13;
int relay_count = 0;
void relay(void) {
    if (!setup_flag) {
        setup_flag = 1;
        M5.Lcd.setCursor(100, 30, 4);
        M5.Lcd.println("RELAY * 8");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN : 13");
        pinMode(In_0, OUTPUT);
        digitalWrite(In_0, LOW);
        relay_count = 0;
        digitalWrite(In_0, HIGH);
    }
    relay_count++;
    if (relay_count > 2000) relay_count = 0;
    // if(relay_count == 1)
    // digitalWrite(In_0, LOW);
    // if(relay_count == 1000)
    digitalWrite(In_0, HIGH);
}
int servo_count = 0;
int freq        = 50;
int ledChannel  = 0;
int resolution  = 8;
void servo() {
    if (!setup_flag) {
        setup_flag = 1;
        gpio_reset_pin(GPIO_NUM_15);

        M5.Lcd.setCursor(100, 30, 4);
        M5.Lcd.println("SERVO");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN : 15");

        ledcSetup(ledChannel, freq, resolution);
        ledcAttachPin(15, ledChannel);
        servo_count = 0;
    }

    servo_count++;
    if (servo_count > 3000) servo_count = 0;
    if ((servo_count / 1000) == 0) {
        ledcWrite(ledChannel, 6);  // 0°
    }
    if ((servo_count / 1000) == 1) {
        ledcWrite(ledChannel, 18);  // 0°
    }

    if ((servo_count / 1000) == 2) {
        ledcWrite(ledChannel, 30);  // 0°
    }
}
const int MOTOR_A = 2;
const int MOTOR_B = 5;
const int MOTOR_C = 12;
const int MOTOR_D = 13;
void stmpmotor(void) {
    if (!setup_flag) {
        setup_flag = 1;
        gpio_reset_pin(GPIO_NUM_2);
        gpio_reset_pin(GPIO_NUM_5);
        gpio_reset_pin(GPIO_NUM_12);
        gpio_reset_pin(GPIO_NUM_13);

        M5.Lcd.setCursor(100, 30, 4);
        M5.Lcd.println("STEPMOTOR");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN :A:2,B:5,C:12,D:13");
        pinMode(MOTOR_A, OUTPUT);
        pinMode(MOTOR_B, OUTPUT);
        pinMode(MOTOR_C, OUTPUT);
        pinMode(MOTOR_D, OUTPUT);
    }

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
MFRC522 mfrc522(0x28);

void ShowReaderDetails() {
    // Get the MFRC522 software version
    byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
    Serial.print(F("MFRC522 Software Version: 0x"));
    Serial.print(v, HEX);
    if (v == 0x91)
        Serial.print(F(" = v1.0"));
    else if (v == 0x92)
        Serial.print(F(" = v2.0"));
    else
        Serial.print(F(" (unknown)"));
    Serial.println("");
    // When 0x00 or 0xFF is returned, communication probably failed
    if ((v == 0x00) || (v == 0xFF)) {
        Serial.println(
            F("WARNING: Communication failure, is the MFRC522 properly "
              "connected?"));
    }
}
void rfid() {
    if (!setup_flag) {
        setup_flag = 1;
        gpio_reset_pin(GPIO_NUM_22);
        gpio_reset_pin(GPIO_NUM_21);
        Wire.begin();  // Initialize I2C

        M5.Lcd.setCursor(140, 30, 4);
        M5.Lcd.print("RFID");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN : SCL:22,SDA:21");
        mfrc522.PCD_Init();   // Init MFRC522
        ShowReaderDetails();  // Show details of PCD - MFRC522 Card Reader
                              // details
        // Serial.println(F("Scan PICC to see UID, type, and data blocks..."));
        // M5.Lcd.println("Scan PICC to see UID, type, and data blocks...");
    }
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        // delay(50);
        // M5.Lcd.println("Scan PICC to see UID, type, and data blocks...");
        // return;
    }

    Serial.print(F("Card UID:"));
    M5.Lcd.println(" ");
    M5.Lcd.setCursor(0, 90, 4);
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        // Serial.print(mfrc522.uid.uidByte[i], HEX);
        // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        // Serial.print(mfrc522.uid.uidByte[i], HEX);
        M5.Lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        M5.Lcd.print(mfrc522.uid.uidByte[i], HEX);
    }
    // Serial.println();
}

SHT3X sht30;
QMP6988 qmp6988;
void env() {
    float tmp = 0.0, hum = 0.0, pressure = 0.0;

    if (!setup_flag) {
        setup_flag = 1;

        M5.Lcd.setCursor(100, 30, 4);
        M5.Lcd.print("ENV Test");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN : SCL:22,SDA:21");
        Wire.begin();  // Wire init, adding the I2C bus.  Wire初始化,
                       // 加入i2c总线
        Serial.printf("qmp6886:%d", qmp6988.init(0x70, &Wire));
    }

    if (sht30.get() == 0) {  // Obtain the data of shT30.  获取sht30的数据
        tmp = sht30.cTemp;   // Store the temperature obtained from shT30.
                             // 将sht30获取到的温度存储
        hum = sht30.humidity;  // Store the humidity obtained from the SHT30.
                               // 将sht30获取到的湿度存储
    } else {
        tmp = 0, hum = 0;
    }
    pressure = qmp6988.calcPressure();
    M5.lcd.fillRect(0, 100, 140, 60,
                    BLACK);  // Fill the screen with black (to clear the
                             // screen).  将屏幕填充黑色(用来清屏)
    M5.Lcd.setCursor(0, 100, 4);
    M5.Lcd.printf("Temp: %2.1f  \r\nHumi: %2.0f%%  \r\nPressure:%2.0fPa\r\n",
                  tmp, hum, pressure);
    delay(2000);
}

const int Analog = 35;
const int Digtal = 2;
uint16_t a_data;
uint16_t d_data;
void luminosity() {
    if (!setup_flag) {
        setup_flag = 1;
        gpio_reset_pin(GPIO_NUM_35);
        gpio_reset_pin(GPIO_NUM_2);

        M5.Lcd.setCursor(80, 30, 4);
        if (count_flag == 7)
            M5.Lcd.print("LUMINOSITY");
        else
            M5.Lcd.print("MICROPHONE");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN : a:35,d:2");

        pinMode(Digtal, INPUT_PULLUP);
    }

    a_data = analogRead(Analog);
    d_data = digitalRead(Digtal);

    Serial.printf("Analog:%0d Digtal:%0d\n", a_data, d_data);

    M5.Lcd.setCursor(30, 120, 4);
    M5.Lcd.printf("Analog:%0d Digtal:%0d\n", a_data, d_data);

    delay(50);
}
int rx_num   = 0;
int rx_count = 0;
void uart232() {
    if (!setup_flag) {
        setup_flag = 1;
        gpio_reset_pin(GPIO_NUM_16);
        gpio_reset_pin(GPIO_NUM_17);
        Serial2.begin(115200, SERIAL_8N1, 16, 17);
        M5.Lcd.setCursor(80, 30, 4);
        M5.Lcd.print("RS232");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN :TX:17,RX:16");
        rx_count = 0;
        rx_num   = 0;
    }

    if (Serial2.available()) {
        int ch = Serial2.read();
        // Serial.write(ch);
        if (ch == 'a') {
            rx_num++;
        }
        M5.Lcd.setCursor(30, 120, 4);
        M5.Lcd.printf("rx_num = %d\n", rx_num);
    }
    rx_count++;
    if (rx_count > 6000) rx_count = 0;
    if (rx_count == 10) Serial2.write('a');
}

// int rx_num = 0;
// int rx_count = 0;
void uart485() {
    if (!setup_flag) {
        setup_flag = 1;
        gpio_reset_pin(GPIO_NUM_16);
        gpio_reset_pin(GPIO_NUM_17);
        gpio_reset_pin(GPIO_NUM_21);
        gpio_reset_pin(GPIO_NUM_22);
        Serial2.begin(115200, SERIAL_8N1, 16, 17);
        Serial1.begin(115200, SERIAL_8N1, 22, 21);
        M5.Lcd.setCursor(80, 30, 4);
        M5.Lcd.print("RS485");
        M5.Lcd.setCursor(0, 60, 4);
        M5.Lcd.println("PIN :TX:17,RX:16");
        rx_count = 0;
        rx_num   = 0;
    }

    if (Serial1.available()) {
        int ch = Serial1.read();
        // Serial.write(ch);
        if (ch == 'a') {
            rx_num++;
        }
        M5.Lcd.setCursor(30, 120, 4);
        M5.Lcd.printf("rx_num = %d\n", rx_num);
    }
    rx_count++;
    if (rx_count > 6000) rx_count = 0;
    if (rx_count == 10) Serial2.write('a');
}
void setup() {
    // put your setup code here, to run once:
    M5.begin();
    dacWrite(25, 0);

    M5.Lcd.setCursor(90, 0, 4);
    M5.Lcd.print("FactoryTest");

    pinMode(37, INPUT_PULLUP);

    M5.Lcd.setCursor(220, 210, 4);
    M5.Lcd.println("mode");
}

void loop() {
    // put your main code here, to run repeatedly:

    if (digitalRead(37) == LOW) {
        count_flag++;
        setup_flag = 0;
        M5.Lcd.fillRect(0, 0, 80, 50, BLACK);
        M5.Lcd.setCursor(0, 0, 4);
        M5.Lcd.println(count_flag);
        M5.Lcd.fillRect(0, 30, 360, 170, BLACK);
        if (count_flag > 16) count_flag = 0;
        while (digitalRead(37) == LOW)
            ;
    }

    switch (count_flag) {
        case 0:
            joystick();
            break;
        case 1:
            dac();
            break;
        case 2:
            adc();
            break;
        case 3:
            encoder();
            break;
        case 4:
            matrix();
            break;
        case 5:
            env();
            break;
        case 6:
            luminosity();
            break;
        case 7:
            key();
            break;
        case 8:
            dcmotor();
            break;
        case 9:
            relay();
            break;
        case 10:
            servo();
            break;
        case 11:
            stmpmotor();
            break;
        case 12:
            rfid();
            break;
        case 13:
            uart232();
            break;
        case 14:
            uart485();
            break;
        default:
            break;
    }
}
