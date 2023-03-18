#include <WiFi.h>
#include <PubSubClient.h>

// Dht additions
#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

// Dht parts
unsigned long previousMillis = 0;  
const long interval = 1000;           // interval at which to blink (milliseconds)

// Ultrasonic Parts
int trigPin = 19;    // TRIG pin
int echoPin = 18;    // ECHO pin
float duration_us, distance_cm;

const char* ssid = "Laye";
const char* password = "kppu3807";

//---- MQTT Broker settings
const char* mqtt_server = "192.168.70.110";
const int mqtt_port = 1883;

#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

const char* sensor1_topic= "espElorm/dht";
const char*  sensor2_topic="espElorm/ultrasonic";

const char* motorControlTopic="espElorm/motorCommand";
const int motorPin = 23;
long lastMsg = 0;
WiFiClient wifiClient;

PubSubClient client(mqtt_server,mqtt_port,wifiClient);

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(motorPin, OUTPUT);
  dht.begin();
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    
    publishMessage(sensor1_topic,String(readDHT()),true);    
    publishMessage(sensor2_topic,String(readUltrasonic()),true);
  }
}

float readDHT(){
  unsigned long currentMillis = millis();
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(t))  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return 0;
  }else{
    return t;
    }
  
}

float readUltrasonic(){
   // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  return distance_cm;
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";   // Create a random client ID
    clientId += String(random(0xffff), HEX);  //you could make this static
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("dht");   // subscribe the topics here
      client.subscribe("ultrasonic");   // subscribe the topics here
      client.subscribe("motorControl");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void publishMessage(const char* topic, String payload , boolean retained){
  if (client.publish(topic, payload.c_str(), true))
      Serial.println("Message publised ["+String(topic)+ "]: "+payload);
      //delay(10);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String incommingMessage = "";
  for (int i = 0; i < length; i++) incommingMessage+=(char)payload[i];
  
  Serial.println("Message arrived ["+String(topic)+" ]"+incommingMessage);
  if( strcmp(topic,motorControlTopic) == 0){
     if (incommingMessage.equals("on")) digitalWrite(motorPin, HIGH);   // Turn the motor on 
     else if (incommingMessage.equals("off"))  digitalWrite(motorPin, LOW);  // Turn the motor off 
  }
}
