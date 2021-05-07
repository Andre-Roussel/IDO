#include <MQTT.h>

const char mqttServer[] = "10.149.130.14"; // IP adress of IDO ThingsBoard Server (Broker) in the classroom
const int mqttServerPort = 1883; // broker mqtt port
const String subTopic = "CMD_Arduino_LED";

const char key[] = "GEc1TeH6bCdIouFNU5yv"; // broker access token
const char secret[] = ""; // broker secret
const char device[] = "c51db830-1523-11eb-aa84-c7eada0320f6"; // broker device identifier




MQTTClient mqqtClient;  // Create a MQTT client to handle messagin between object and broker


void messageReceived(String &topic, String &payload) {
 
  Serial.println(payload);
 
  cmd_Openhab_LED = payload;
  

}

void SendBasicPayload(String mqttSubject, String mqttMessage){

  mqqtClient.publish(mqttSubject, mqttMessage);
  Serial.print(mqttSubject);
  Serial.print("   ");
  Serial.println(mqttMessage);

}


void MQTTConnect() {
  
  mqqtClient.begin(mqttServer, mqttServerPort, wifiClient);
  Serial.print("Connecting to broker...");
  mqqtClient.onMessage(messageReceived);
  while (!mqqtClient.connect(device, key, secret)) {
    Serial.print(".");
    delay(1000);
  }
  mqqtClient.subscribe(subTopic);
  Serial.println("\nConnected to MQTT!\n");

}
