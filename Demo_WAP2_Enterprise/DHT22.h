//Setup for DHT22

#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22  
DHT dhtSensor(DHTPIN, DHTTYPE); //Define and create the correct DHT sensor instance

void dhtBegin()
{
  dhtSensor.begin();
}

float dhtHumidity()
{
  return dhtSensor.readHumidity();
}

float dhtTemperature()
{
  return dhtSensor.readTemperature();
}
