#ifndef __LED
#define __LED


#include <Adafruit_NeoPixel.h>

int LEDColor_RED = 0;
int LEDColor_BLUE = 0;
int LEDColor_GREEN = 0;
int LEDColor_BRIGHTNESS = 0;




Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, MLED_PIN, NEO_GRB);


void LED_SetColor(int iGREEN, int iRED, int iBLUE, int iBrightness){
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(iGREEN, iRED, iBLUE));
        Serial.print("Set pixel ");
        Serial.println(i);
    }
    strip.setBrightness(iBrightness);
    strip.show(); // Call to update the LEDs with the new color
    Serial.print("Gone through setcolor with ");
    Serial.print(iGREEN);
    Serial.print(" ");
    Serial.print(iRED);
    Serial.print(" ");
    Serial.print(iBLUE);
    Serial.print(" ");
    Serial.print(iBrightness);
    Serial.println(" ");
}



void LED_setup(){
  strip.begin();
//  strip.setBrightness(255);
//  strip.show(); // Initialize all pixels to 'off'
}




#endif