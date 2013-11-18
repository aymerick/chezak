// References:
//  - https://github.com/nathanchantrell/TinyTX/blob/master/TinyTX_DHT22/TinyTX_DHT22.ino
//  - https://github.com/mharizanov/TinySensor/blob/master/Funky_DHT22/Funky_DHT22.ino

#include <DHT22.h>

// Power wire is plugged into jeenode DI03 (arduino: digital 6)
#define DHTPowerPin 6
// Data wire is plugged into jeenode DI02 (arduino: digital 5)
#define DHTDataPin 5

DHT22 myDHT22(DHTDataPin);

void setup() {
  // start serial port
  Serial.begin(57600);
  Serial.println("DHT22 Pin Powered Test");
}

void loop() {
  DHT22_ERROR_t errorCode;

  // power on sensor
  pinMode(DHTPowerPin,OUTPUT);
  digitalWrite(DHTPowerPin,HIGH);

  delay(2000);

  Serial.print("Requesting data...");
  errorCode = myDHT22.readData();

  // power off sensor
  digitalWrite(DHTPowerPin,LOW);

  switch(errorCode)
  {
    case DHT_ERROR_NONE:
      Serial.print("Got Data ");
      Serial.print(myDHT22.getTemperatureC());
      Serial.print("C ");
      Serial.print(myDHT22.getHumidity());
      Serial.println("%");
      // Alternately, with integer formatting which is clumsier but more compact to store and
      // can be compared reliably for equality:
      //
      char buf[128];
      sprintf(buf, "Integer-only reading: Temperature %hi.%01hi C, Humidity %i.%01i %% RH",
                   myDHT22.getTemperatureCInt()/10, abs(myDHT22.getTemperatureCInt()%10),
                   myDHT22.getHumidityInt()/10, myDHT22.getHumidityInt()%10);
      Serial.println(buf);
      break;
    case DHT_ERROR_CHECKSUM:
      Serial.print("check sum error ");
      Serial.print(myDHT22.getTemperatureC());
      Serial.print("C ");
      Serial.print(myDHT22.getHumidity());
      Serial.println("%");
      break;
    case DHT_BUS_HUNG:
      Serial.println("BUS Hung ");
      break;
    case DHT_ERROR_NOT_PRESENT:
      Serial.println("Not Present ");
      break;
    case DHT_ERROR_ACK_TOO_LONG:
      Serial.println("ACK time out ");
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
      Serial.println("Sync Timeout ");
      break;
    case DHT_ERROR_DATA_TIMEOUT:
      Serial.println("Data Timeout ");
      break;
    case DHT_ERROR_TOOQUICK:
      Serial.println("Polled to quick ");
      break;
  }
}
