// Testing AM2302 sensor (aka DHT22) on Jeenode with lib: https://github.com/adafruit/DHT-sensor-library

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
// Modified by Aymerick for jeenode use

// NOTE:
// - Humidity value seems correct
// - Temperature seems 1.8 *C greater than correct value

#include "DHT.h"

#define DHTPIN 4     // Jeenode: Port 1 DI01 - Arduino: Digital 4

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +3.3V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 4.7K resistor from pin 2 (data) to +3.3V

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(57600);
  Serial.println("DHTxx test!");

  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");
  }
  delay(3000);
}
