/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-toggle-led
 */

#include "WIFIConnector.h"
#include "MQTTConnector.h"

// constants won't change
const int BUTTON_PIN = 2; // Arduino pin connected to button's pin
const int LED_PIN    = 6; // Arduino pin connected to LED's pin

// variables will change:
int ledState = LOW;     // the current state of LED
int lastButtonState;    // the previous state of button
int currentButtonState; // the current state of button

void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(LED_PIN, OUTPUT);          // set arduino pin to output mode

  currentButtonState = digitalRead(BUTTON_PIN);

  wifiConnect();
  MQTTConnect();
  
}

void loop() {

  //allow the client to process incoming messages and maintain its connection to the server.
  mqqtClient.loop(); 
  
  lastButtonState    = currentButtonState;      // save the last state
  currentButtonState = digitalRead(BUTTON_PIN); // read new state

  if(lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println();

    // toggle state of LED
    ledState = !ledState;
    if(ledState)
    {
      SendBasicPayload("LED_ON_OFF", "ON");
    }
    else
    {
      SendBasicPayload("LED_ON_OFF", "OFF");
    }
    

    // control LED arccoding to the toggled state
    digitalWrite(LED_PIN, ledState); 
  }
}
