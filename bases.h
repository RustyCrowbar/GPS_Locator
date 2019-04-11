void baseRainbow()
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
}

void baseHomogenousR()
{
    for (uint8_t u = 0; u < NB_LEDS; u++)
        leds[u] = CRGB(0, 0, 255);
}

void baseHomogenousG()
{
    for (uint8_t u = 0; u < NB_LEDS; u++)
        leds[u] = CRGB(0, 255, 0);
}

void baseHomogenousB()
{
    for (uint8_t u = 0; u < NB_LEDS; u++)
        leds[u] = CRGB(255, 0, 0);
}
