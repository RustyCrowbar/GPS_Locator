void genericProgressBar(CRGB off_color)
{
    static bool filling = true;
    static uint16_t on_index = 0;
    static uint16_t tmp;
    for (tmp = 0; tmp < on_index; tmp++)
        leds[tmp] = filling ? current_base[tmp] : off_color;
    for (; tmp < NB_LEDS; tmp++)
        leds[tmp] = filling ? off_color : current_base[tmp];
    if (++on_index == NB_LEDS)
    {
        filling = !filling;
        on_index = 0;
    }
    delay(60);
}

void patternProgressBarR()
{
    genericProgressBar(red_led);
}

void patternProgressBarG()
{
    genericProgressBar(green_led);
}

void patternProgressBarB()
{
    genericProgressBar(blue_led);
}

void patternProgressBarOff()
{
    genericProgressBar(off_led);
}

/*void patternProgressBarFade()
{
    static bool filling = true;
    static bool is_new = true;
    static const uint8_t base_divider = 16;
    static uint8_t inc = 2;
    static uint16_t on_index = 0;
    static uint16_t tmp;
    static CRGB off = CRGB(0, 0, 0);
    for (tmp = 0; tmp < on_index; tmp++)
        leds[tmp] = filling ? current_base[tmp] : off;
    for (; tmp < NB_LEDS; tmp++)
        leds[tmp] = filling ? off : current_base[tmp];
    if (filling)
    {
        if (on_index > 0)
        {
            if (leds[on_index - 1] == current_base[on_index - 1])
            {
                if (is_new)
                {
                    leds[on_index - 1] /= base_divider;
                    is_new = false;
                }
                else
                {
                    on_index++;
                    is_new = true;
                }
            }
            else
                leds[on_index - 1] *= 2;
        }
        else
            on_index++;
    }
    else
    {
        
    }
    if (on_index == NB_LEDS)
    {
        filling = !filling;
        on_index = 0;
    }
    delay(10);
}*/

void patternPulse()
{
    static bool inc = 1;
    if (brightness < 0)
    {
        brightness = 1;
        inc = 1;
    }
    else if (brightness >= MAX_BRIGHTNESS)
    {
        brightness = MAX_BRIGHTNESS;
        inc = 0;
    }
    //FastLED.setBrightness(leds, NB_LEDS, inc ? b++ : b--);
    FastLED.setBrightness(inc ? brightness++ : brightness--);
}

void patternFlashSlow()
{
    static bool on = true;
    FastLED.setBrightness(on ? brightness : 0);
    on = !on;
    delay(200);
}

void patternRoll()
{
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

void patternCenter()
{
    static bool filling = true;
    static uint16_t on_index = 0;
    static uint16_t tmp;
    static CRGB off = CRGB(0, 0, 0);
    for (tmp = 0; tmp < on_index; tmp++)
    {
        leds[tmp] = filling ? current_base[tmp] : off;
        leds[NB_LEDS - tmp - 1] = filling ? current_base[NB_LEDS - tmp - 1] : off;
    }
    for (; tmp <= NB_LEDS / 2; tmp++)
    {
        leds[tmp] = filling ? off : current_base[tmp];
        leds[NB_LEDS - tmp - 1] = filling ? off : current_base[NB_LEDS - tmp - 1];
    }
    if (on_index++ == NB_LEDS / 2)
    {
        filling = !filling;
        on_index = 0;
    }
    delay(50);
}

void patternStatic()
{
    delay(300);
}
