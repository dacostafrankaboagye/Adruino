#include<DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
float hum, temp;

const int ledPin = 13; // yellow or orange LED
const int redLedPin = 5;
const int blueLedPin = 3;  // green led
const int ldrPin = A0;
int ledState = LOW;
int redLedState = LOW;
int blueLedState = LOW;
const long ledInterval = 600;  //600ms
const long dhtInterval = 2500; // 2.5s
unsigned long previousMillisLed = 0;
unsigned long previousMillisDht = 0;

void setup(){
  pinMode(ledPin,OUTPUT);
  pinMode(redLedPin,OUTPUT);
  pinMode(ldrPin,INPUT);
  Serial.begin(9600);
  dht.begin();
}

void ledAction(unsigned long currentMillisLed){
  
    if(ledState == LOW){
      ledState = HIGH;
      Serial.print("Light ON");
      
    }else{
      ledState = LOW;
      Serial.print("Light OFF");
    }

    Serial.print("\ncurrent Millis() = ");
    Serial.print(currentMillisLed);
    digitalWrite(ledPin, ledState);
    Serial.print("\n");  
}

void redLedAction(float temp){
  if(temp > 26.0){
    redLedState = HIGH;
  }
  else{redLedState = LOW;}
  digitalWrite(redLedPin, redLedState);
}

void dhtAction(unsigned long currentMillisDht, int ldrStatus){
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  // turn on and off red LED
  redLedAction(temp);


  if(ldrStatus > 120){
    blueLedState = HIGH;
  }else{blueLedState=LOW;}

  digitalWrite(blueLedPin, blueLedState);
  
  

  Serial.print("++++++++++++++++++++\nHumidity= ");
  Serial.print(hum);
  Serial.print(" Temperature= ");
  Serial.print(temp);
  Serial.print("\ncurrent Millis() = ");
  Serial.print(currentMillisDht);
  Serial.print("\n++++++++++++++++++++\n\n");
    
}



void loop(){

  unsigned long currentMillisLed = millis();
  unsigned long currentMillisDht = millis();
  int ldrStatus = analogRead(ldrPin);
  
  
  unsigned long differenceLed = (currentMillisLed - previousMillisLed);
  unsigned long differenceDht = (currentMillisDht - previousMillisDht);

  
  
  if(differenceLed == ledInterval){
    ledAction(currentMillisLed);
    previousMillisLed = currentMillisLed;
    //Serial.print(ldrStatus);    
  }
  if(differenceDht == dhtInterval){
    dhtAction(currentMillisDht,ldrStatus);
    previousMillisDht = currentMillisDht;
  }
    if(ldrStatus > 120){
    blueLedState = HIGH;
  }else{blueLedState=LOW;}

  digitalWrite(blueLedPin, blueLedState);

    
}
  
    
