#include "DHT.h"

#define DHTPIN 23
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  delay(2000);
  // The DHT22 returns at most one measurement every 2s
  float h = dht.readHumidity();
  // Reads the humidity in %
  float t = dht.readTemperature();
  // Reads the temperature in degrees Celsius
  float f = dht.readTemperature(true);
  // true returns the temperature in Fahrenheit

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed reception"));
    
    // Returns an error if the ESP32 does not receive any measurements
  }

  Serial.print("Humidite: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(t);
  Serial.print("°C, ");
  Serial.print(f);
  Serial.println("°F");
  // Transmits the received measurements to the serial terminal via USB
}
