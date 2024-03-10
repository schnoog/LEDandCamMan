#include <Arduino.h>
#include <EEPROM.h>
#define MLED_PIN 13

#define LEDNUM 7

#define SERVO1_PIN 12
#define SERVO2_PIN 11

#include <neoled.h>
#include <camservo.h>
#include <homewifi.h>





void setup()
{
  EEPROM.begin(512);
  Serial.begin(115200);
  delay(5000);
  servo_setup();
  wifi_setup();
  Serial.println();
  Serial.println("setup done");
}


void loop()
{
  wifi_loop();
}

