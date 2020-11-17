/* 
 *  
 *  
 *  
 *  
 */



#include "WIFIConnector.h"
#include "MQTTConnector.h"
#include "DHT22.h"
#include "OLED_Basic.h"




void setup() 
{
  
  Serial.begin(9600);

  wifiConnect();
  MQTTConnect();

  //begin DHT22
  dhtBegin();

  //Begin OLED Display
  oledBegin();
  

}

void loop() 
{

  //allow the client to process incoming messages and maintain its connection to the server.
  mqqtClient.loop(); 
  // check for WiFi OTA updates
  ArduinoOTA.poll();

  
  basicPrintOLED("Temperature", dhtTemperature(), "C");
  basicPrintOLED("Humidity", dhtHumidity(), "%");

  KeyValue[0]= dhtHumidity();
  KeyValue[1]= dhtTemperature();
      
  SendPayload(TelemetryKey,KeyValue);

}
