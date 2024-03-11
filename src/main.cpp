#include <Arduino.h>

#define MLED_PIN 13

#define LEDNUM 7

#define SERVO1_PIN 12
#define SERVO2_PIN 11


#include <neoled.h>
#include <camservo.h>
#include <homewifi.h>
#include <projeeprom.h>




void setup()
{
  EEPROM.begin(512);
  Serial.begin(115200);
  servo_setup();
  wifi_setup();
  Serial.println();
  Serial.println("setup done - switching LEDs on");
  LED_SetColor(255,255,255,255);
}


void loop()
{
  wifi_loop();
}

