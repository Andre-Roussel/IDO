#include <MQTT.h>

const char mqttServer[] = "10.149.130.14"; // IP adress of IDO ThingsBoard Server (Broker) in the classroom
const int mqttServerPort = 1883; // broker mqtt port

const char key[] = "GEc1TeH6bCdIouFNU5yv"; // broker access token
const char secret[] = ""; // broker secret
const char device[] = "c51db830-1523-11eb-aa84-c7eada0320f6"; // broker device identifier


//Modify this section to reflect the number of telemetry keys your are using

//NumberOfTelemetryKeys is the number of values that are sent via MQTT to the broker
//MaxLenghtTelemetryKeyName is the maximum lenght of the key name

const int NumberOfTelemetryKeys = 2;
const int MaxLenghtTelemetryKeyName = 50;


// Array to hold the values (take a look in the loop function

float KeyValue[NumberOfTelemetryKeys];


// Define your key names here
char  TelemetryKey[NumberOfTelemetryKeys][MaxLenghtTelemetryKeyName]={
  "Taille_cm",
  "test"
  
};

MQTTClient mqqtClient;  // Create a MQTT client to handle messagin between object and broker


void messageReceived(String &topic, String &payload) {
 
  Serial.println(payload);
  //Serial.println(payload.substring(31,payload.length() -2));
  //ledDelay = payload.substring(31,payload.length() -2).toInt();
  Serial.println("Message received");

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
  mqqtClient.subscribe("LED_ON_OFF");
  Serial.println("\nConnected to MQTT!\n");

}

void SendPayload(char TelemetryKey[NumberOfTelemetryKeys][MaxLenghtTelemetryKeyName],float KeyValue[NumberOfTelemetryKeys])
{

char attributes[200];

String payload = "{";
  for (int i=0; i < NumberOfTelemetryKeys; i++)
  {
    payload += "\"" + String(TelemetryKey[i]) + "\":";
    payload += String(KeyValue[i]);

    if(i != NumberOfTelemetryKeys-1)
    {
      payload +=",";
    }
   
  }

  payload += "}";

  payload.toCharArray(attributes, 100);
  mqqtClient.publish("testswitch002", "OFF");
  Serial.println(attributes);

}
