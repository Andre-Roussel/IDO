/*

Template to use GSM infrastructure to send MQTT message to thingsboard broker
 
*/

#include "Connector_GSM_MQTT.h";

int pinStatus = 1;

unsigned long lastMillis = 0;  //Used instead of delay to send data every 10 seconds

void messageReceived(String &topic, String &payload) {
  

  Serial.println(payload);
  //Serial.println(payload.substring(45,payload.length() -3));
  Serial.println("Message received");


  
}

void setup() {
   // Initialize serial and wait for port to open:
   Serial.begin(9600);
   
  //Connect using the proper mode (wifi, bluetootj, gsm, etc...) Proper Connector_XXX_XXX.h library must be included
  connect();

  pinMode(LED_BUILTIN, OUTPUT);

 
}




void loop() {
 mqqtClient.loop(); //allow the client to process incoming messages and maintain its connection to the server.

    
    
    
    if (millis() - lastMillis > 1000) 
    {

      if(pinStatus == 1)
      {
        digitalWrite(LED_BUILTIN,pinStatus);
        pinStatus =0;
      }
      else {
      digitalWrite(LED_BUILTIN,pinStatus);
        pinStatus =1;
      }

      KeyValue[0]= pinStatus;
    
      SendPayload(TelemetryKey,KeyValue);
       
      lastMillis = millis();
    }
}
