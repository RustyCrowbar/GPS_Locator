#include "GPS_Locator.h"

TinyGPSPlus gps;

void rainbowCircle()
{
  uint8_t coeff = 0xff * 6 / NB_LEDS;
  static uint8_t u;
  static uint8_t tmp;
  for (u = 0; u < (NB_LEDS / 6); u++) {
      //0 - nb/6:            R: 255; G: 0 - 255; B: 0
      leds[u] = CRGB(255, u * coeff, 0);
  }
  tmp = 0;
  for (; u < (NB_LEDS / 3); u++) {
      //nb/6 - 2nb/6:     R: 255 - 0; G: 255; B: 0
      leds[u] = CRGB(255 - tmp * coeff, 255, 0);
      tmp++;
  }
  tmp = 0;
  for (; u < (NB_LEDS / 2); u++) {
      //2nb/6 - 3nb/6:    R: 0; G: 255; B: 0 - 255
      leds[u] = CRGB(0, 255, tmp * coeff);
      tmp++;
  }
  tmp = 0;
  for (; u < (2 * NB_LEDS / 3); u++) {
      //3nb/6 - 4nb/6:    R: 0; G: 255 - 0; B: 255
      leds[u] = CRGB(0, 255 - tmp * coeff, 255);
      tmp++;
  }
  tmp = 0;
  for (; u < (5 * NB_LEDS / 6); u++) {
      //4nb/6 - 5nb/6:    R: 0 - 255; G: 0; B: 255
      leds[u] = CRGB(tmp * coeff, 0, 255);
      tmp++;
  }
  tmp = 0;
  for (; u < NB_LEDS; u++) {
      //5nb/6 - nb:       R: 255; G: 0; B: 255 - 0
      leds[u] = CRGB(255, 0, 255 - tmp * coeff);
      tmp++;
  }

  for (uint8_t u = 0; u < NB_LEDS; u++) { //The number of iterations actually doesn't have to be NB_LEDS
    static CRGB tmp;
    static CRGB *p;
    static uint8_t index;
    tmp = leds[NB_LEDS - 1];
    for (index = NB_LEDS - 1; index > 0; index--) {
        p = leds + index - 1;
        leds[index] = *p;
    }
    leds[0] = tmp;
    delay(10);
  }
}

bool satelitesAcquired()
{
  return gps.location.isUpdated();
}

void showNorth(uint16_t heading)
{
  /*static uint8_t r[NB_LEDS] = 0;
  static uint8_t g[NB_LEDS] = 0;
  static uint8_t b[NB_LEDS] = 0;*/
  heading += ANGLE_CORRECTION;
  heading %= 360;
  //Serial.print("Heading: ");
  //Serial.println(heading);
  uint16_t quadrant = 360 / (NB_LEDS - 1);
  uint16_t min;
  uint16_t max;
  for (uint8_t u = 0; u < NB_LEDS - 1; u++) {
    min = u * quadrant;
    max = min + quadrant;
    leds[u + 1] = CRGB(0, 255 * (min < heading && heading <= max), 0);
    //Serial.print("u:"); Serial.print(u); Serial.print("; min:"); Serial.print(min); Serial.print("; max:"); Serial.println(max);
  }
  /*for (uint8_t u = 0; u < NB_LEDS; u++) {
    leds[u] = CRGB(r[u], g[u], b[u]);
  }*/
  FastLED.show();
}

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

  //Initialize GPS

  //Wait for the GPS to acquire satelites
  while (satelitesAcquired())
    rainbowCircle();
}

void loop()
{
  //Get data from GPS

  //Get data from magnetometer
  /*HMC6352.Wake();
  int north = HMC6352.GetHeading();
  HMC6352.Sleep();
  Serial.println(north);*/
  int x = 0;
  int y = 0;
  int z = 0; //triple axis data

  //Tell the HMC what register to begin writing data into

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
  /*Serial.print("X Value: ");
  Serial.println(x);
  Serial.print("Y Value: ");
  Serial.println(y);
  Serial.print("Z Value: ");
  Serial.println(z);
  Serial.println();*/
  
  float heading=atan2(x, y)/0.0174532925;
  if(heading < 0) heading+=360;
  heading=360-heading; // N=0/360, E=90, S=180, W=270

  //Display the direction
  showNorth(heading);
  /*for (uint8_t u = 0; u < NB_LEDS; u++)
  {
    leds[u] = 0xFF0000;
    FastLED.show();
    delay(100);
  }
  delay(200);
  for (uint8_t u = 0; u < NB_LEDS; u++)
  {
    leds[u] = 0x00FF00;
    FastLED.show();
    delay(100);
  }*/

  delay(100);
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
