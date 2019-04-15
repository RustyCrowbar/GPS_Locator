#include "GPS_Locator.h"

void setup()
{
  Serial.begin(115200);

  FastLED.addLeds<NEOPIXEL, 2>(leds, NB_LEDS); FastLED.setBrightness(1);

  Wire.begin();
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x0B); // Tell the HMC5883 to Continuously Measure
  Wire.write(0x01); // Set the Register
  Wire.endTransmission();
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x09); // Tell the HMC5883 to Continuously Measure
  Wire.write(0x1D); // Set the Register
  Wire.endTransmission();
}

void loop()
{
  for (uint8_t u = 0; u < NB_LEDS; u++)
  {
    leds[u] = 0xFF0000;
    FastLED.show();
    delay(100);
  }
  delay(1000);
  for (uint8_t u = 0; u < NB_LEDS; u++)
  {
    leds[u] = 0x00FF00;
    FastLED.show();
    delay(100);
  }

  int x, y, z; //triple axis data

  //Tell the HMC what regist to begin writing data into

  Wire.beginTransmission(addr);
  Wire.write(0x00); //start with register 3.
  Wire.endTransmission();

  //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(addr, 6);
  if (6 <= Wire.available()) {
    x = Wire.read(); //MSB  x
    x |= Wire.read() << 8; //LSB  x
    z = Wire.read(); //MSB  z
    z |= Wire.read() << 8; //LSB z
    y = Wire.read(); //MSB y
    y |= Wire.read() << 8; //LSB y
  }

  // Show Values
  Serial.print("X Value: ");
  Serial.println(x);
  Serial.print("Y Value: ");
  Serial.println(y);
  Serial.print("Z Value: ");
  Serial.println(z);
  Serial.println();

  delay(500);
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
