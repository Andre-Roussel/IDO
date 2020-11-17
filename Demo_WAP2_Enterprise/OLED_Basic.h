#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);


void oledBegin()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void basicPrintOLED(String text, float value, String units)
{
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(text);
  display.setTextSize(3);
  display.setCursor(0,8);
  display.print(value);
  display.print(" " + units);
  display.display();

  delay(2000);
}
