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
int brightness = 0;

TFT_eSPI tft =  TFT_eSPI();

void show_yes()
{
    tft.pushImage(0, 0, 128, 128, image_yes);

    for (brightness = 255; brightness >= 0; brightness--) { // decrease brightness
        analogWrite(PIN_LCD_BL, brightness);  // set the LED brightness
        delay(1);  // wait a little bit to see the effect
    }

    for (brightness = 0; brightness <= 255; brightness++) { // increase brightness
        analogWrite(PIN_LCD_BL, brightness);  // set the LED brightness
        delay(5);  // wait a little bit to see the effect
    }

}

void show_no()
{
    tft.pushImage(0, 0, 128, 128, image_no);

    for (brightness = 255; brightness >= 0; brightness--) { // decrease brightness
        analogWrite(PIN_LCD_BL, brightness);  // set the LED brightness
        delay(1);  // wait a little bit to see the effect
    }

    for (brightness = 0; brightness <= 255; brightness++) { // increase brightness
        analogWrite(PIN_LCD_BL, brightness);  // set the LED brightness
        delay(5);  // wait a little bit to see the effect
    }

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
    pinMode(PIN_LCD_BL, OUTPUT);
}

void loop()
{

    if (millis() - button_time > 150)
    {
        if (digitalRead(PIN_BTN_L) == 0)
        {
            if (random(2) == 0) {
                show_yes();
            } else {
                show_no();
            }
            button_time = millis();

        }
        else if (digitalRead(PIN_BTN_R) == 0)
        {
            show_no();
            button_time = millis();
        }
        else
        {
            analogWrite(PIN_LCD_BL, 255);
            tft.fillScreen(TFT_BLACK);
            button_time = millis();
            
        }
    }

}