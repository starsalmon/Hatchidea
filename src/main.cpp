#include "Arduino.h"
#include <TFT_eSPI.h>
#include "image_yes.c"
#include "image_no.c"

#define SCREEN_WIDTH         128
#define SCREEN_WIDTH         128


#define PIN_BAT_VOLT         4
#define PIN_BTN_L            0
#define PIN_BTN_R            47
#define PIN_LCD_BL           10

uint button_time = 0;

TFT_eSPI tft =  TFT_eSPI();

void show_yes()
{
    tft.pushImage(0, 0, 128, 128, image_yes);
    delay(20);
}

void show_no()
{
    tft.pushImage(0, 0, 128, 128, image_no);
    delay(20);
}



void setup()
{
    Serial.begin(115200);
    Serial.println("Hello T-QT");

    tft.begin();
    tft.setRotation(2);
    tft.setSwapBytes(true); // Required when using pushImage

    pinMode(PIN_BTN_L, INPUT_PULLUP);
    pinMode(PIN_BTN_R, INPUT_PULLUP);
}

void loop()
{

    if (millis() - button_time > 150)
    {
        if (digitalRead(PIN_BTN_L) == 0)
        {
            show_yes();
            button_time = millis();
        }
        else if (digitalRead(PIN_BTN_R) == 0)
        {
            show_no();
            button_time = millis();
        }
        else
        {
            tft.fillScreen(TFT_BLACK);
            button_time = millis();
        }
    }

}