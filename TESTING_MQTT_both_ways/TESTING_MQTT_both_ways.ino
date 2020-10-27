//Be sure to modify the MQTTConnector.h and WIFIConnector.h info to connect your
//object to the thingsBoard server

#include "WIFIConnector.h"
#include "MQTTConnector.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


WiFiClient wifiClient;  // Create a WIFI client to connected to the net
MQTTClient mqqtClient;  // Create a MQTT client to handle messagin between object and broker



int pin;
int LED_PIN=2;

String payload;

//Generic connection function 

void connect() {
  
  InitWifiConnection(); // Establish the WIFI connection (Infrastructure)
  InitMQTTConnection(); // Establish the MQTT connection (Messaging)
  
}

void InitMQTTConnection() {
  
  mqqtClient.begin(mqttServer, mqttServerPort, wifiClient);
  mqqtClient.onMessage(messageReceived);
  Serial.print("Connecting to broker...");
  
  while (!mqqtClient.connect(device, key, secret)) {
    Serial.print(".");
    delay(1000);
  }

  mqqtClient.subscribe("v1/devices/me/rpc/request/+");
  Serial.println("\nConnected to MQTT!\n");
 
}

void gotIt()
{
  Serial.println("Got it");
}

void InitWifiConnection() {

  Serial.print("Connecting to wifi...");
  
  while ( status != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println("\nConnected to WiFi!\n");

}


void messageReceived(String &topic, String &payload) {
  lcd.clear();

  Serial.println(payload);
  Serial.println(payload.substring(45,payload.length() -3));
  Serial.println("Message received");

  lcd.backlight();
lcd.setCursor(0,0);
lcd.print(payload.substring(45,payload.length() -3));

  
}


void setup() {

  Serial.begin(9600);
  connect();   //Establish WIFI and MQTT Connections
  lcd.begin();
  
}


 // Prepare a JSON payload string
String prepareJSONstring(int on){

String payload = "{";
  payload += "\"On =1 Off = 0\":"; 
  payload += on; 
  payload += "}";

 return payload;
}

void SendMessage(String payload){
  // Send payload
  char attributes[100];
  payload.toCharArray(attributes, 100);
  mqqtClient.publish("v1/devices/me/telemetry", attributes);
  Serial.println(attributes);
}

void loop() {
  mqqtClient.loop(); //allow the client to process incoming messages and maintain its connection to the server.
/*
 if(WiFi.status()==3 && mqqtClient.connected())  // Does connection still existe
 {


      digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      pin = 1;
      payload = prepareJSONstring(pin); // Prepare message
      SendMessage(payload); // Send the message to broker
  
  delay(2000);                       // wait for a second
        digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
        pin = 0;
        payload = prepareJSONstring(pin); // Prepare message
        SendMessage(payload); // Send the message to broker
  delay(2000); 
    
        
    
        
      
        
     
   }
 else //connection lost so reconnect
 {
    status=WL_IDLE_STATUS;
    WiFi.end();
    connect();
 }
 */
}
