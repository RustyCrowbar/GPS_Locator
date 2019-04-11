//#include "GPS_Locator.h"
//#define F_CPU 16500000L
#include <FastLED.h>

#define NUM_LEDS 7

CRGB leds[NUM_LEDS];
void setup() { FastLED.addLeds<NEOPIXEL, 1>(leds, NUM_LEDS); FastLED.setBrightness(1);}
void loop() {
  for (uint8_t u = 0; u < NUM_LEDS; u++)
  {
    leds[u] = CRGB::White;
    FastLED.show();
    delay(100);
  }
  delay(1000);
  for (uint8_t u = 0; u < NUM_LEDS; u++)
  {
    leds[u] = CRGB::Black;
    FastLED.show();
    delay(100);
  }
}
/*
void setup()
{
  cli();
  pinMode(0, INPUT_PULLUP); //Push button to GND
  //pinMode(1, OUTPUT); //On-board LED
  FastLED.addLeds<NEOPIXEL, 1, 2>(leds, NB_LEDS);
  FastLED.setBrightness(brightness);
  GIMSK |= (1 << PCIE);
  PCMSK |= (1 << PCINT0); //INT for button 0
  sei();
}

void loop()
{
    if (change_base)
        changeBase();
    if (change_pattern)
        changePattern();
    patterns[pattern]();
    FastLED.show();
    delay(30);
}

#include "bases.h"
#include "patterns.h"

void save_base()
{
    memcpy(current_base, leds, NB_LEDS * sizeof(*leds));
}

void changeBase()
{
    change_base = false;
    bases[(++base) % NB_BASES]();
    save_base();
}

void changePattern()
{
    change_pattern = false;
    pattern = (++pattern) % NB_PATTERNS;
}

ISR(PCINT0_vect)
{
    delayMicroseconds(10000); //For debouncing purposes //10ms
  if (!digitalRead(0)) //Button is pressed
  {
    delayMicroseconds(10000); //For debouncing purposes //10ms
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes //100ms
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes //200ms
    if (!digitalRead(0)) //Intentionnal long press: alternate function
        change_base = true;
    else //Short press function
        change_pattern = true;
  }
  else
  {
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes
    delayMicroseconds(10000); //For debouncing purposes //100ms
  }
}*/
