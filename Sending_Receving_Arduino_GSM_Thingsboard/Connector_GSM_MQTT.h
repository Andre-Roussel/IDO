#include <MKRGSM.h>

#include "GSMConnector.h";

#include "MQTTConnector.h";




// Please enter your sensitive data in the Secret tab or arduino_secrets.h
// PIN Number
const char PINNUMBER[]     = SECRET_PINNUMBER;
// APN data
const char GPRS_APN[]      = SECRET_GPRS_APN;
const char GPRS_LOGIN[]    = SECRET_GPRS_LOGIN;
const char GPRS_PASSWORD[] = SECRET_GPRS_PASSWORD;

//Modify this section to reflect the number of telemetry keys your are using

//NumberOfTelemetryKeys is the number of values that are sent via MQTT to the broker
//MaxLenghtTelemetryKeyName is the maximum lenght of the key name

const int NumberOfTelemetryKeys = 1;
const int MaxLenghtTelemetryKeyName = 50;


// Array to hold the values (take a look in the loop function

float KeyValue[NumberOfTelemetryKeys];


// Define your key names here
char  TelemetryKey[NumberOfTelemetryKeys][MaxLenghtTelemetryKeyName]={
  "LED ON/OFF"
};






// initialize the library instance
GSMClient GSMclient;
GPRS gprs;
GSM gsmAccess;

MQTTClient mqqtClient;  // Create a MQTT client to handle messagin between object and broker

void InitGSMConnection() {

  Serial.print("Connecting to GSM...");
  
  // connection state
 bool connected = false;

 // After starting the modem with GSM.begin()
 // attach the shield to the GPRS network with the APN, login and password
 while (!connected) {
   if ((gsmAccess.begin(PINNUMBER) == GSM_READY) &&
       (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY)) {
     connected = true;
   } else {
     Serial.println("Not connected");
     delay(1000);
   }
 }


  
  Serial.println("\nConnected to GSM!\n");

}

void InitMQTTConnection() {
  
  mqqtClient.begin(mqttServer, mqttServerPort, GSMclient);
  Serial.print("Connecting to broker...");
  
  while (!mqqtClient.connect(device, key, secret)) {
    Serial.print(".");
    delay(1000);
  }
  mqqtClient.subscribe("v1/devices/me/rpc/request/+");
  Serial.println("\nConnected to MQTT!\n");

}

void connect() {
  
  InitGSMConnection(); // Establish the GSM connection (Infrastructure)
  InitMQTTConnection(); // Establish the MQTT connection (Messaging)

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

  payload.toCharArray(attributes, 200);
  mqqtClient.publish("v1/devices/me/telemetry", attributes);
  Serial.println(attributes);

}
