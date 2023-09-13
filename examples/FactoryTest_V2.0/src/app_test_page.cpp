#include "app_test_page.h"

uint8_t page_status = PAGE_DAC;
uint8_t flag_i2c_test_failed = 0;

void page_dac_test(void)
{
  if (i2c_check(DAC_ADDR)) {
    M5.Display.startWrite();
    if (flag_i2c_test_failed) {
        init_dac_test();
        M5.Display.clear(WHITE);
        flag_i2c_test_failed = 0;
    }    
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 150, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("DAC 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("SCL -> 22   SDA -> 21");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);

    M5.Display.setCursor(100, 60);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("DAC电压");

    M5.Display.setTextColor(BLUE);
    M5.Display.setTextSize(3);
    M5.Display.setCursor(100, 90);
    M5.Display.printf("1.25V");
    M5.Display.setCursor(100, 120);
    M5.Display.printf("2.50V");
    M5.Display.setCursor(100, 150);
    M5.Display.printf("3.75V");
    M5.Display.setCursor(100, 180);
    M5.Display.printf("5.00V");
    M5.Display.setTextSize(2);

    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();
  }
  else {
    if (!flag_i2c_test_failed) {
        M5.Display.clear(WHITE);
        flag_i2c_test_failed = 1;
    }        
    flag_i2c_test_failed = 1;
    M5.Display.startWrite();
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 150, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("DAC 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("SCL -> 22   SDA -> 21");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);

    M5.Display.setCursor(130, 90);
    M5.Display.setTextColor(RED);
    M5.Display.printf("请接线");

    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();      
  }

  M5.update();
  if (M5.BtnA.wasClicked()) {
    page_status = PAGE_KEYBOARD;
    init_keyboard();
    flag_i2c_test_failed = 0;
    M5.Display.startWrite();
    M5.Display.clear(WHITE);
    M5.Display.endWrite();  
  } else if (M5.BtnC.wasClicked()) {
    page_status = PAGE_ADC;
    init_adc_test();
    flag_i2c_test_failed = 0;
    M5.Display.startWrite();
    M5.Display.clear(WHITE);
    M5.Display.endWrite(); 
  }
}

void page_adc_test(void)
{
  float adc_result[4] = {0.0};

  if (i2c_check(ADC_ADDR)) {
    M5.Display.startWrite();
    if (flag_i2c_test_failed) {
        init_adc_test();
        M5.Display.clear(WHITE);
        flag_i2c_test_failed = 0;
    }    
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 150, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("ADC 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("SCL -> 22   SDA -> 21");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);

    M5.Display.setCursor(100, 60);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("ADC电压");

    adc_result[0] = readChannel(ADS1115_COMP_0_GND);
    adc_result[1] = readChannel(ADS1115_COMP_1_GND);
    adc_result[2] = readChannel(ADS1115_COMP_2_GND);
    adc_result[3] = readChannel(ADS1115_COMP_3_GND);

    M5.Display.setTextColor(BLUE);
    M5.Display.setTextSize(3);
    M5.Display.setCursor(80, 90);
    M5.Display.fillRect(80, 90, 200, 30, WHITE);
    M5.Display.printf("CH0:%.2fV", adc_result[0]);
    M5.Display.setCursor(80, 120);
    M5.Display.fillRect(80, 120, 200, 30, WHITE);
    M5.Display.printf("CH1:%.2fV", adc_result[1]);
    M5.Display.setCursor(80, 150);
    M5.Display.fillRect(80, 150, 200, 30, WHITE);
    M5.Display.printf("CH2:%.2fV", adc_result[2]);
    M5.Display.setCursor(80, 180);
    M5.Display.fillRect(80, 180, 200, 30, WHITE);
    M5.Display.printf("CH3:%.2fV", adc_result[3]);
    M5.Display.setTextSize(2);

    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();
  }
  else {
    if (!flag_i2c_test_failed) {
        M5.Display.clear(WHITE);
        flag_i2c_test_failed = 1;
    }        
    flag_i2c_test_failed = 1;
    M5.Display.startWrite();
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 150, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("ADC&DAC 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("SCL -> 22   SDA -> 21");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);

    M5.Display.setCursor(130, 90);
    M5.Display.setTextColor(RED);
    M5.Display.printf("请接线");

    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();      
  }

  M5.update();

  if (M5.BtnA.wasClicked()) {
    page_status = PAGE_DAC;
    init_dac_test();
    flag_i2c_test_failed = 0;
    M5.Display.startWrite();
    M5.Display.clear(WHITE);
    M5.Display.endWrite();  
  } else if (M5.BtnC.wasClicked()) {
    page_status = PAGE_RFID;
    init_rfid();
    flag_i2c_test_failed = 0;
    M5.Display.startWrite();
    M5.Display.clear(WHITE);
    M5.Display.endWrite(); 
  }
}

void page_rfid_test(void)
{
    static byte rf_uid[500] = {0};
    static byte rf_length = 0;

    M5.Display.startWrite();
    if (flag_i2c_test_failed) {
        if (i2c_check(0x28)) {
            M5.Display.clear(WHITE);
            init_rfid();
            flag_i2c_test_failed = 0;
        }
    }   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 150, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("RFID 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("SCL -> 22   SDA -> 21");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);

    if (i2c_check(0x28)) {
        ShowReaderDetails(rf_uid, &rf_length);
        M5.Display.setCursor(10, 80);
        M5.Display.setTextColor(BLACK);
        // M5.Display.printf("固件版本:");
        // if (init_status) {
        //     M5.Display.setTextColor(GREEN);
        //     M5.Display.fillRect(120, 80, 200, 30, WHITE);
        //     M5.Display.setTextSize(3);
        //     M5.Display.printf("通过");            
        // }
        // else {
        //     M5.Display.setTextColor(RED);
        //     M5.Display.fillRect(120, 80, 200, 30, WHITE);
        //     M5.Display.setTextSize(3);
        //     M5.Display.printf("不通过");               
        // }
        M5.Display.setTextSize(2);
        M5.Display.setCursor(10, 140);
        M5.Display.setTextColor(BLACK);
        M5.Display.printf("UID:");
        M5.Display.setTextSize(3);
        M5.Display.setTextColor(BLUE);
        M5.Display.fillRect(60, 140, 260, 30, WHITE);
        M5.Display.fillRect(0, 170, 320, 30, WHITE);
        for (byte i = 0; i < rf_length; i++) {
            M5.Display.printf("%02X", rf_uid[i]);
        }
        M5.Display.setTextSize(2);
    }  
    else {
        flag_i2c_test_failed = 1;
        M5.Display.setCursor(130, 110);
        M5.Display.setTextColor(RED);
        M5.Display.printf("请接线");        
    }   
    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_ADC;
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();    
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_TEMP;
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();    
    }
}

void page_temp_test(void)
{
    static float temp, hum;

    M5.Display.startWrite();
    if (flag_i2c_test_failed) {
        if (i2c_check(0x44)) {
            M5.Display.clear(WHITE);
            flag_i2c_test_failed = 0;
        }
    }    
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 130, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("温湿度 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("SCL -> 22   SDA -> 21");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);

    if (i2c_check(0x44)) {
        get_sht30_info(&temp, &hum, 1000);
        M5.Display.setCursor(10, 110);
        M5.Display.setTextColor(BLACK);
        M5.Display.printf("温度:");
        if (temp >= 16.0f && temp <= 40.0f) {
            M5.Display.setTextColor(GREEN);
        }
        else {
            M5.Display.setTextColor(RED);
        }
        M5.Display.fillRect(70, 110, 200, 30, WHITE);
        M5.Display.setTextSize(3);
        M5.Display.printf("%.2f", temp);
        M5.Display.setTextSize(2);
        M5.Display.setCursor(10, 140);
        M5.Display.setTextColor(BLACK);
        M5.Display.printf("湿度:");
        if (hum >= 30.0f && hum <= 98.0f) {
            M5.Display.setTextColor(GREEN);
        }
        else {
            M5.Display.setTextColor(RED);
        } 
        M5.Display.fillRect(70, 140, 200, 30, WHITE);
        M5.Display.setTextSize(3);
        M5.Display.printf("%.2f", hum);               
        M5.Display.setTextSize(2);
    }  
    else {
        flag_i2c_test_failed = 1;
        M5.Display.setCursor(130, 110);
        M5.Display.setTextColor(RED);
        M5.Display.printf("请接线");        
    } 

    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_RFID;
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_AIR_PRESSURE;
        flag_i2c_test_failed = 0;
        init_qmp6988();
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_pressure_test(void)
{
    static float qmp_pressure;

    M5.Display.startWrite();
    if (flag_i2c_test_failed) {
        if (i2c_check(0x70)) {
            init_qmp6988();
            M5.Display.clear(WHITE);
            flag_i2c_test_failed = 0;
        }
    }    
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 110, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("气压 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("SCL -> 22   SDA -> 21");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);

    if (i2c_check(0x70)) {
        get_qmp6988_info(&qmp_pressure);
        M5.Display.setCursor(10, 110);
        M5.Display.setTextColor(BLACK);
        M5.Display.printf("气压:");
        if (qmp_pressure >= 100000.0f) {
            M5.Display.setTextColor(GREEN);
        }
        else {
            M5.Display.setTextColor(RED);
        }
        M5.Display.setTextSize(3);
        M5.Display.fillRect(70, 110, 200, 30, WHITE);
        M5.Display.printf("%.2f", qmp_pressure);               
        M5.Display.setTextSize(2);
    }  
    else {
        flag_i2c_test_failed = 1;
        M5.Display.setCursor(130, 110);
        M5.Display.setTextColor(RED);
        M5.Display.printf("请接线");        
    } 

    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_TEMP;
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_LUMINOSITY;
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_luminosity_test(void)
{
    static uint16_t lumi_analog, lumi_digital;

    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 180, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("luminosity 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Analog->35  Digital->2");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);

    luminosity(&lumi_analog, &lumi_digital);
    M5.Display.setCursor(10, 110);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Analog:");
    M5.Display.setTextColor(BLUE);
    M5.Display.fillRect(90, 110, 200, 30, WHITE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", lumi_analog);
    M5.Display.setTextSize(2);
    M5.Display.setCursor(10, 140);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Digital:");
    M5.Display.fillRect(100, 140, 200, 30, WHITE);
    M5.Display.setTextColor(BLUE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", lumi_digital);
    M5.Display.setTextSize(2);    

    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_AIR_PRESSURE;
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_MICROPHONE;
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_microphone_test(void)
{
    static uint16_t microphone_analog, microphone_digital;

    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 180, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("microphone 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Analog->35  Digital->2");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);

    microphone(&microphone_analog, &microphone_digital);
    M5.Display.setCursor(10, 110);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Analog:");
    M5.Display.setTextColor(BLUE);
    M5.Display.fillRect(90, 110, 200, 30, WHITE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", microphone_analog);
    M5.Display.setTextSize(2);
    M5.Display.setCursor(10, 140);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Digital:");
    M5.Display.fillRect(100, 140, 200, 30, WHITE);
    M5.Display.setTextColor(BLUE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", microphone_digital);
    M5.Display.setTextSize(2);    

    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_LUMINOSITY;
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_RS485;
        gpio_reset_pin(GPIO_NUM_21);
        gpio_reset_pin(GPIO_NUM_22); 
        init_rs485();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_rs485_test(void)
{
    static uint16_t microphone_analog, microphone_digital;

    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 130, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("RS485 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("TX -> 17   RX -> 16");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);

    
    M5.Display.setCursor(10, 110);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("接收次数:");
    M5.Display.setTextColor(BLUE);
    M5.Display.fillRect(120, 110, 200, 30, WHITE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", uart485());
    M5.Display.setTextSize(2);
  

    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_MICROPHONE;
        gpio_reset_pin(GPIO_NUM_21);
        gpio_reset_pin(GPIO_NUM_22); 
        M5.Ex_I2C.begin(I2C_PORT, I2C_SDA, I2C_SCL);          
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_RS232;
        gpio_reset_pin(GPIO_NUM_21);
        gpio_reset_pin(GPIO_NUM_22); 
        init_rs232();
        M5.Ex_I2C.begin(I2C_PORT, I2C_SDA, I2C_SCL);       
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_rs232_test(void)
{
    static uint16_t microphone_analog, microphone_digital;

    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 130, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("RS232 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("TX -> 17   RX -> 16");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);

    
    M5.Display.setCursor(10, 110);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("接收次数:");
    M5.Display.setTextColor(BLUE);
    M5.Display.fillRect(120, 110, 200, 30, WHITE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", uart232());
    M5.Display.setTextSize(2);
  

    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_RS485;
        gpio_reset_pin(GPIO_NUM_21);
        gpio_reset_pin(GPIO_NUM_22); 
        init_rs485();         
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_RELAY;
        init_relay();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_relay_test(void)
{
    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 130, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("Relay 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("PIN -> 13");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);
  

    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_RS232;
        init_rs232();         
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_RGB;
        init_rgb();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_rgb_test(void)
{
    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 130, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("RGB 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("PIN -> 13");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);
  
    matrix();
    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_RELAY;
        init_relay();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_SERVO;
        init_servo();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_servo_test(void)
{
    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 130, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("Servo 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("PIN -> 13");
    M5.Display.drawFastHLine(5, 60, 310, BLACK);
  
    servo();
    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_RGB;
        init_rgb();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_JOYSTICK;
        init_joystick();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_joystick_test(void)
{
    static uint16_t x_adc, y_adc;
    static uint8_t button;
    
    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 180, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("Joystick 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("x_adc->2 y_adc->13");
    M5.Display.setCursor(10, 60);
    M5.Display.printf("button->15");
    M5.Display.drawFastHLine(5, 90, 310, BLACK);
  
    joystick(&x_adc, &y_adc, &button);
    M5.Display.setCursor(10, 110);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("X_ADC:");
    M5.Display.setTextColor(BLUE);
    M5.Display.fillRect(85, 110, 200, 30, WHITE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", x_adc);
    M5.Display.setTextSize(2);
    M5.Display.setCursor(10, 140);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Y_ADC:");
    M5.Display.setTextColor(BLUE); 
    M5.Display.fillRect(85, 140, 200, 30, WHITE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", y_adc);               
    M5.Display.setTextSize(2);    
    M5.Display.setCursor(10, 170);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Button:");
    M5.Display.setTextColor(BLUE); 
    M5.Display.fillRect(90, 170, 200, 30, WHITE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", button);               
    M5.Display.setTextSize(2);    
    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_SERVO;
        init_servo();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_ENCODER;
        init_encoder(true);
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_encoder_test(void)
{
    static uint32_t encoder_counter;
    static uint8_t button;
    
    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 180, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("Encoder 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("A->2 B->13");
    M5.Display.setCursor(10, 60);
    M5.Display.printf("Button->15");
    M5.Display.drawFastHLine(5, 90, 310, BLACK);
  
    get_encoder(&encoder_counter, &button, true);
    M5.Display.setCursor(10, 110);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Encoder:");
    M5.Display.setTextColor(BLUE);
    M5.Display.fillRect(105, 110, 200, 30, WHITE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", encoder_counter);
    M5.Display.setTextSize(2);
    M5.Display.setCursor(10, 140);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Button:");
    M5.Display.setTextColor(BLUE); 
    M5.Display.fillRect(90, 140, 200, 30, WHITE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", button);               
    M5.Display.setTextSize(2);    
    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_JOYSTICK;
        init_joystick();        
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_DC_MOTOR;
        init_dc_motor();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_dcmotor_test(void)
{
    static uint32_t encoder_counter;
    static uint8_t button;
    
    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 180, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("DCMotor 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("M+->12 M-->15");
    M5.Display.setCursor(10, 60);
    M5.Display.printf("EN_A->2 EN_B->13");
    M5.Display.drawFastHLine(5, 90, 310, BLACK);
  
    dcmotor();
    get_encoder(&encoder_counter, &button, false);
    M5.Display.setCursor(10, 110);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Encoder:");
    M5.Display.setTextColor(BLUE);
    M5.Display.fillRect(105, 110, 200, 30, WHITE);
    M5.Display.setTextSize(3);
    M5.Display.printf("%d", encoder_counter);              
    M5.Display.setTextSize(2);    
    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_ENCODER;
        init_encoder(true);        
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_STEP_MOTOR;
        init_step_motor();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_stepmotor_test(void)
{
    static uint32_t encoder_counter;
    static uint8_t button;
    
    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 180, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("StepMotor 测试");
    M5.Display.setCursor(10, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("A->12 B->15");
    M5.Display.setCursor(10, 60);
    M5.Display.printf("C->2 D->13");
    M5.Display.drawFastHLine(5, 90, 310, BLACK);
  
    step_motor();           
    M5.Display.setTextSize(2);    
    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_DC_MOTOR;
        init_dc_motor();
        init_encoder(false);        
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_KEYBOARD;
        init_keyboard();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}

void page_keyboard_test(void)
{
    static char k = 0;
    static char k_show = 0;
    
    M5.Display.startWrite();   
    M5.Display.setCursor(80, 0);
    M5.Display.drawRect(80, 0, 180, 30, BLUE);
    M5.Display.setTextColor(BLACK);
    M5.Display.setTextSize(2);
    M5.Display.print("Keyboard 测试");
    M5.Display.setCursor(0, 30);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("R0:5 R1:12 R2:13 R3:15");
    M5.Display.setCursor(0, 60);
    M5.Display.printf("C0:17 C1:16 C2:21 C3:22");
    M5.Display.drawFastHLine(5, 90, 310, BLACK);
  
    k = keyboard(); 
    if (k_show != k && k != 0 )
        k_show = k;       
    M5.Display.setCursor(10, 110);
    M5.Display.setTextColor(BLACK);
    M5.Display.printf("Key:");
    M5.Display.setTextColor(BLUE);
    M5.Display.fillRect(60, 110, 200, 50, WHITE);
    M5.Display.setTextSize(3);
    if (k_show != 0)
        M5.Display.printf("%c", k_show);   
    else {
        M5.Display.printf(" ", k_show); 
    }
    M5.Display.setTextSize(2);    
    M5.Display.setTextColor(BLACK);
    M5.Display.drawString("[上一步]", 20, 215);
    // M5.Display.drawString("[]", 20, 200);
    M5.Display.drawString("[下一步]", 220, 215);  
    M5.Display.endWrite();

    M5.update();

    if (M5.BtnA.wasClicked()) {
        page_status = PAGE_STEP_MOTOR;
        init_step_motor();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    } else if (M5.BtnC.wasClicked()) {
        page_status = PAGE_DAC;
        init_dac_test();
        flag_i2c_test_failed = 0;
        M5.Display.startWrite();
        M5.Display.clear(WHITE);
        M5.Display.endWrite();        
    }
}