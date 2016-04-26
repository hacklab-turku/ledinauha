#include <NeoPixelBus.h>
#include "parse.h"
#include "parse.c"
unsigned long showtime;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(N_LEDS, 2);


void setup()
{
    Serial.begin(74880);
    while(!Serial);

    Serial.print("Hello!\nTalk to me like this:\n<LED_NUMBER> <R> <G> <B>\\n\nSource available at https://github.com/hacklab-turku/ledinauha\nN_LEDS: ");
    Serial.println(N_LEDS,DEC);
    Serial.print("brightness values between 0-127\nenjoy!\n");

    strip.Begin();
    //strip.Show();
    showtime=millis();
}

void loop()
{
  //noInterrupts();
  uint8_t show_flag = 0;
  uint8_t i;
    for(i = 0; i < N_LEDS; i++) {
      if(led[i][3]) {
        strip.SetPixelColor(i, RgbColor(led[i][1],led[i][0],led[i][2]));
        led[i][3] = 0;
        show_flag = 1;
      }
    }
  if (show_flag&&millis()-showtime>16) {
  strip.Show();
  showtime=millis();
  }
  //interrupts();
}

char rawBytesLeft = 0;

void serialEvent()
{
  while(Serial.available()>0)
  {
    char data=Serial.read();
    //Serial.write(data);
    /*if (rawBytesLeft == 0) {
      if (data > 127) {
        rawBytesLeft = 3;
        Serial.println(rawBytesLeft, DEC);*/
        int out = rawParse(data);
        if (out == 1) {
          Serial.write(out);
        }
      /*} else {
        cmdParse(data);
      }
    } else {
      rawParse(data);
      rawBytesLeft--;
      Serial.println(rawBytesLeft, DEC);
    }*/
  }
}

