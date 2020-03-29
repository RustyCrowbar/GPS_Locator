#include "GPS_Locator.h"

void rainbowCircle()
{
  uint8_t coeff = 0xff * 6 / (NB_LEDS - 1);
  static uint8_t u;
  static uint8_t tmp;
  for (u = 0; u < ((NB_LEDS - 1) / 6); u++) {
      //0 - nb/6:            R: 255; G: 0 - 255; B: 0
      leds[u] = CRGB(255, u * coeff, 0);
  }
  tmp = 0;
  for (; u < ((NB_LEDS - 1) / 3); u++) {
      //nb/6 - 2nb/6:     R: 255 - 0; G: 255; B: 0
      leds[u] = CRGB(255 - tmp * coeff, 255, 0);
      tmp++;
  }
  tmp = 0;
  for (; u < ((NB_LEDS - 1) / 2); u++) {
      //2nb/6 - 3nb/6:    R: 0; G: 255; B: 0 - 255
      leds[u] = CRGB(0, 255, tmp * coeff);
      tmp++;
  }
  tmp = 0;
  for (; u < (2 * (NB_LEDS - 1) / 3); u++) {
      //3nb/6 - 4nb/6:    R: 0; G: 255 - 0; B: 255
      leds[u] = CRGB(0, 255 - tmp * coeff, 255);
      tmp++;
  }
  tmp = 0;
  for (; u < (5 * (NB_LEDS - 1) / 6); u++) {
      //4nb/6 - 5nb/6:    R: 0 - 255; G: 0; B: 255
      leds[u] = CRGB(tmp * coeff, 0, 255);
      tmp++;
  }
  tmp = 0;
  for (; u < (NB_LEDS - 1); u++) {
      //5nb/6 - nb:       R: 255; G: 0; B: 255 - 0
      leds[u] = CRGB(255, 0, 255 - tmp * coeff);
      tmp++;
  }

  for (uint8_t u = 0; u < NB_LEDS; u++) { //The number of iterations actually doesn't have to be NB_LEDS
    static CRGB tmp;
    static CRGB *p;
    static uint8_t index;
    tmp = leds[NB_LEDS - 1];
    for (index = NB_LEDS - 1; index > 1; index--) {
        p = leds + index - 1;
        leds[index] = *p;
    }
    leds[1] = tmp;
    FastLED.show();
    delay(200);
  }
}

bool satelitesAcquired()
{
  while (gpsSerial.available() > 0)
  {
    //delay(1);
    char read = gpsSerial.read();
    gps.encode(read);
    Serial.print(read);
    //Serial.println("'");
  //Serial.println(gps.location.lat(), 6); // Latitude in degrees (double)
  //Serial.println(gps.location.lng(), 6); // Longitude in degrees (double)
  //Serial.print(gps.location.rawLat().negative ? "-" : "+");
  //Serial.println(gps.location.rawLat().deg); // Raw latitude in whole degrees
  //Serial.println(gps.location.rawLat().billionths);// ... and billionths (u16/u32)
  //Serial.print(gps.location.rawLng().negative ? "-" : "+");
  //Serial.println(gps.location.rawLng().deg); // Raw longitude in whole degrees
  //Serial.println(gps.location.rawLng().billionths);// ... and billionths (u16/u32)
  //Serial.println(gps.date.value()); // Raw date in DDMMYY format (u32)
  //Serial.println(gps.date.year()); // Year (2000+) (u16)
  //Serial.println(gps.date.month()); // Month (1-12) (u8)
  //Serial.println(gps.date.day()); // Day (1-31) (u8)
  //Serial.println(gps.time.value()); // Raw time in HHMMSSCC format (u32)
  //Serial.println(gps.time.hour()); // Hour (0-23) (u8)
  //Serial.println(gps.time.minute()); // Minute (0-59) (u8)
  //Serial.println(gps.time.second()); // Second (0-59) (u8)
  //Serial.println(gps.time.centisecond()); // 100ths of a second (0-99) (u8)
  //Serial.println(gps.speed.value()); // Raw speed in 100ths of a knot (i32)
  //Serial.println(gps.speed.knots()); // Speed in knots (double)
  //Serial.println(gps.speed.mph()); // Speed in miles per hour (double)
  //Serial.println(gps.speed.mps()); // Speed in meters per second (double)
  //Serial.println(gps.speed.kmph()); // Speed in kilometers per hour (double)
  //Serial.println(gps.course.value()); // Raw course in 100ths of a degree (i32)
  //Serial.println(gps.course.deg()); // Course in degrees (double)
  //Serial.println(gps.altitude.value()); // Raw altitude in centimeters (i32)
  //Serial.println(gps.altitude.meters()); // Altitude in meters (double)
  //Serial.println(gps.altitude.miles()); // Altitude in miles (double)
  //Serial.println(gps.altitude.kilometers()); // Altitude in kilometers (double)
  //Serial.println(gps.altitude.feet()); // Altitude in feet (double)
  //Serial.println(gps.satellites.value()); // Number of satellites in use (u32)
  //Serial.println(gps.hdop.value()); // Horizontal Dim. of Precision (100ths-i32)
  }
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
  Serial.println("========== RESET ==========");

  FastLED.addLeds<NEOPIXEL, 2>(leds, NB_LEDS); FastLED.setBrightness(BRIGHTNESS);
  for (uint8_t u = 0; u < NB_LEDS; u++)
    leds[u] = red_led;
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
  gpsSerial.begin(9600); // connect gps sensor

  Serial.println("========== Printing raw NMEA data ==========");
  //Wait for the GPS to acquire satelites
  while (!satelitesAcquired())
    rainbowCircle();
  Serial.println("========== Acquired a position! ==========");
  for (uint8_t u = 0; u < NB_LEDS; u++)
    leds[u] = green_led;
  FastLED.show();
  delay(20000);
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
