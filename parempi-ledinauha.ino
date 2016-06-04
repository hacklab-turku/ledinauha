#include <NeoPixelBus.h>

#define N_LEDS 50

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(N_LEDS, 2);

short currentLed = 0;
short colorCounter = 0;
short currentColor[3];

void setup() {
  Serial.begin(115200);
  while(!Serial);

  strip.Begin();
  strip.Show();

}

void loop() {
  while (Serial.available() > 0) {
    char data = Serial.read();
    if (data & 0x80) {    //if high bit is set, new command begins
      currentLed = 0;
      data = data & 0x7f; //mask high bit!
    }
    
    currentColor[colorCounter] = data;
    colorCounter++;

    if (colorCounter > 2) {
      colorCounter = 0;
      strip.SetPixelColor(currentLed, RgbColor(currentColor[0], currentColor[1], currentColor[2]));
      currentLed++;
    }
    
    if (currentLed >= N_LEDS) {
      currentLed = 0;
      colorCounter = 0;
      strip.Show();
    }
  }
}
