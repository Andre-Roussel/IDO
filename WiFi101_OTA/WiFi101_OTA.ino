/*

Demo

Minimum needed for over the air update
Connect your arduino to usb port
Flash the code
Use the IP port to update the arduino over the air

  */
 
#include <SPI.h>
#include <WiFi101.h>
#include <WiFi101OTA.h>

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
/////// Wifi Settings ///////
char ssid[] = SECRET_SSID;      // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password

int status = WL_IDLE_STATUS;

void setup() {
  //Initialize serial:
  Serial.begin(9600);

   pinMode(LED_BUILTIN, OUTPUT);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  }

  // start the WiFi OTA library with internal (flash) based storage
  WiFiOTA.begin("MKR1000_01", "password", InternalStorage);

  
}

void loop() {
  // check for WiFi OTA updates
  WiFiOTA.poll();

  // add your normal loop code below ...


    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second

  
}
