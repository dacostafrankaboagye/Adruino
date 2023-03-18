

#include <DHT.h>;

//Constants
#define DHTPIN 15   
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE); 

int chk;
float hum;  
float temp; 

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
    delay(2000);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(10000); //Delay 2 sec.
}

   
