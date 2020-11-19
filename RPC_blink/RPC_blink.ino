/* 
 *  
 *  
 *  
 *  
 */

int ledDelay;

#include "WIFIConnector.h"
#include "MQTTConnector.h"



unsigned long time_now = 0;
bool  led_Status = HIGH;
void setup() 
{
  
  Serial.begin(9600);

  wifiConnect();
  MQTTConnect();

  pinMode(LED_BUILTIN, OUTPUT);
  

}

void loop() 
{

  //allow the client to process incoming messages and maintain its connection to the server.
  mqqtClient.loop(); 
  // check for WiFi OTA updates
  ArduinoOTA.poll();


    if(millis() >= time_now + ledDelay){
        time_now += ledDelay;
        digitalWrite(LED_BUILTIN, led_Status);
        led_Status = !led_Status;
    }


/*
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  KeyValue[0]= 1;
  Serial.println("High");
  //SendPayload(TelemetryKey,KeyValue);
  delay(2000);                       // wait for a second
  
  
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  KeyValue[0]= 0;
  Serial.println("Low");
  //SendPayload(TelemetryKey,KeyValue);
  delay(2000);
  
*/

}
