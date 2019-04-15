#pragma once

//LEDs
#include <FastLED.h>
#define NB_LEDS 7
//#define MAX_BRIGHTNESS 20 //Between 0 and 255
CRGB leds[NB_LEDS];
CRGB current_base[NB_LEDS];
CRGB off_led = CRGB(0, 0, 0);
CRGB red_led = CRGB(0, 0, 255);
CRGB green_led = CRGB(0, 255, 0);
CRGB blue_led = CRGB(255, 0, 0);

//Magnetometer
#include <Wire.h> //I2C Arduino Library
#define addr 0x0D //I2C Address for The HMC5883
