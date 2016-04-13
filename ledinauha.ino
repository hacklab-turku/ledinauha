#include <NeoPixelBus.h>
#include "parse.h"
#include "parse.c"


NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(N_LEDS, 2);


void setup()
{
    Serial.begin(9600);
    while(!Serial);

    strip.Begin();
    strip.Show();
}

void loop()
{
  uint8_t i;
  for(i = 0; i < N_LEDS; i++)
    strip.SetPixelColor(i, RgbColor(led[i][0],led[i][1],led[i][2]));
  strip.Show();
}

void serialEvent()
{
  while(Serial.available()>0)
  {
    char data=Serial.read();
    Serial.write(data);
    cmdParse(data);
  }
}

