# My ESP32(S2) based 3D printer lighting and camera servo

## What it contains

- An ESP32 connected (via a buck converter) to the 24V power line of my Ender-3 V3 SE printer
- Two small servos working as gimbal for my Raspberry Pi camera
- A strip of 7 WS2812 LEDs (aka Neopixel)

## What it does

- Connects to my local WiFi
- Offers a small and simple web-interface to
  - move the camera
  - change the lighing (color, brightness)
  - perform Over-the-Air (OTA) updates

