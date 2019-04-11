#pragma once

//#define FASTLED_FORCE_SOFTWARE_SPI
//#define SPI_DATA

//#if !defined (FASTLED_ALL_PINS_HARDWARE_SPI)
//# pragma message "FASTLED_ALL_PINS_HARDWARE_SPI is not defined."
//#endif

#include <FastLED.h>

#define NB_LEDS 5
#define MAX_BRIGHTNESS 20 //Between 0 and 255
//#define DATA_PIN 1
//#define CLOCK_PIN 2
CRGB leds[NB_LEDS];
CRGB current_base[NB_LEDS];
CRGB off_led = CRGB(0, 0, 0);
CRGB red_led = CRGB(0, 0, 255);
CRGB green_led = CRGB(0, 255, 0);
CRGB blue_led = CRGB(255, 0, 0);
int16_t brightness = MAX_BRIGHTNESS;

void patternProgressBarR();
void patternProgressBarG();
void patternProgressBarB();
void patternProgressBarOff();
//void patternProgressBarFade();
void patternPulse();
void patternFlashSlow();
void patternRoll();
void patternCenter();
void patternStatic();
//#define NB_PATTERNS 10
#define NB_PATTERNS 9
static void (*patterns[NB_PATTERNS])(void) =
{
      patternProgressBarR,
      patternProgressBarG,
      patternProgressBarB,
      patternProgressBarOff,
      //patternProgressBarFade,
      patternPulse,
      patternFlashSlow,
	  patternRoll,
      patternCenter,
      patternStatic
};
//volatile uint8_t pattern = 4; //Fade
volatile uint8_t pattern = 6; //Roll
volatile bool change_pattern = false;

void baseRainbow();
void baseHomogenousR();
void baseHomogenousG();
void baseHomogenousB();
#define NB_BASES 4
static void (*bases[NB_BASES])(void) =
{
    baseRainbow,
	baseHomogenousR,
	baseHomogenousG,
	baseHomogenousB
};
volatile uint8_t base = -1;
volatile bool change_base = true;
