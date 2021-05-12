#include <Arduino.h>

int ledDelay;

#include "WIFIConnector.h"
#include "MQTTConnector.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        2 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels




unsigned long time_now = 0;
bool  led_Status = HIGH;
void setup() 
{
  
  Serial.begin(9600);
  Serial.print("Made it in the setup");
  wifiConnect();
  MQTTConnect();

  ledDelay=1000;
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

}

void loop() 
{

  //allow the client to process incoming messages and maintain its connection to the server.
  mqqtClient.loop(); 
  // check for WiFi OTA updates
  //ArduinoOTA.poll();


    if(millis() >= time_now + ledDelay){
        time_now += ledDelay;
        if(led_Status)
        {
            for(int i=0; i<NUMPIXELS; i++) 
            { 
              pixels.setPixelColor(i, pixels.Color(255, 255, 255));
            }

          pixels.show();   // Send the updated pixel colors to the hardware.
          Serial.println("On");    
          led_Status = !led_Status;
        }
        else
        {
          pixels.clear();
          pixels.show();
          led_Status = !led_Status;
          Serial.println("Off");
        }
    }




}
