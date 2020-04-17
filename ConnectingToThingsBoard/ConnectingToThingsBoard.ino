//Be sure to modify the MQTTConnector.h and WIFIConnector.h info to connect your
//object to the thingsBoard server

#include "WIFIConnector.h"
#include "MQTTConnector.h";

#include "DHT.h"

#define DHTPIN 2 
#define DHTTYPE DHT22  


WiFiClient wifiClient;  // Create a WIFI client to connected to the net
MQTTClient mqqtClient;  // Create a MQTT client to handle messagin between object and broker


DHT dht(DHTPIN, DHTTYPE); //Define and create the correct DHT sensor instance

unsigned long lastMillis = 0;  //Used instead of delay to send data every second


//Generic connection function 

void connect() {
  
  InitWifiConnection(); // Establish the WIFI connection (Infrastructure)
  InitMQTTConnection(); // Establish the MQTT connection (Messaging)

}

void InitMQTTConnection() {
  
  mqqtClient.begin(mqttServer, mqttServerPort, wifiClient);
  Serial.print("Connecting to broker...");
  
  while (!mqqtClient.connect(device, key, secret)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConnected to MQTT!\n");

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

/*
void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}
*/

void setup() {

  delay(15000); // 
  Serial.begin(9600);
  connect();   //Establish WIFI and MQTT Connections
  dht.begin(); //Start communication with DHT22 sensor
  Serial.println("Sending information");
}


 // Prepare a JSON payload string
String prepareJSONstring(float t,float h){

String payload = "{";
  payload += "\"temperature\":"; 
  payload += t; 
  payload += ",";
  payload += "\"humidity\":"; 
  payload += h;
  payload += "}";

 return payload;
}

void loop() {
  mqqtClient.loop(); //allow the client to process incoming messages and maintain its connection to the server.

  if (millis() - lastMillis > 1000) {
    lastMillis = millis();

    float h = dht.readHumidity();  // Get temperature
    float t = dht.readTemperature(); // Get Humidity

    String payload = prepareJSONstring(t,h); // Prepare message
    SendMessage(payload); // Send the message to broker
  
    lastMillis = millis();
  }
}

void SendMessage(String payload){
  // Send payload
  char attributes[100];
  payload.toCharArray(attributes, 100);
  mqqtClient.publish("v1/devices/me/telemetry", attributes);
  Serial.println(attributes);
}
