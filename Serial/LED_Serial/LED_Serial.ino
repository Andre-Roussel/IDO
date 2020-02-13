const int ledPin = 2;

void setup() {
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
 
   int brightness;

  // check if data has been sent from the computer:
  if (Serial.available()>1) 
  {
   
    Serial.print("Serial Available ");

    //Check the number of values available
    Serial.println(Serial.available());
     
    // read the most recent byte (which will be from 0 to 255):
    brightness = Serial.parseInt();
   
    Serial.print("Brightness ");
    Serial.println(brightness);

     // set the brightness of the LED:
    analogWrite(ledPin, brightness);
  }
}
