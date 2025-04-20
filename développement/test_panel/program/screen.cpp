#include "screen.h"


Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void init_screen()
{
  tft.init(240, 320);
  tft.setRotation(1);
}
