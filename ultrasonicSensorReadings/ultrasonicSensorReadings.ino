//
//
//
//#define echoPin 2 
//#define trigPin 3 
//
//
//long duration; 
//int distance; 
//
//void setup() {
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT); 
//  Serial.begin(9600); // 
//  Serial.println("Ultrasonic Sensor HC-SR04 Test");
//  Serial.println("with Arduino UNO R3");
//}
//void loop() {
//  
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
// 
//  duration = pulseIn(echoPin, HIGH);
//  
//  distance = duration * 0.034 / 2; 
//  
//  Serial.print("Distance: ");
//  Serial.print(distance);
//  Serial.println(" cm");
//}













//
//
//const int trigPin = 22;
//const int echoPin = 25 ;
//
////define sound speed in cm/uS
//#define SOUND_SPEED 0.034
//#define CM_TO_INCH 0.393701
//
//long duration;
//float distanceCm;
//float distanceInch;
//
//void setup() {
//  Serial.begin(115200); // Starts the serial communication
//  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//}
//
//void loop() {
//  // Clears the trigPin
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  
//  // Reads the echoPin, returns the sound wave travel time in microseconds
//  duration = pulseIn(echoPin, HIGH);
//  
//  // Calculate the distance
//  distanceCm = duration * SOUND_SPEED/2;
//  
//  // Convert to inches
//  distanceInch = distanceCm * CM_TO_INCH;
//  
//  // Prints the distance in the Serial Monitor
//  Serial.print("Distance (cm): ");
//  Serial.println(distanceCm);
//  Serial.print("Distance (inch): ");
//  Serial.println(distanceInch);
//  
//  delay(1000);
//}





























/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-ultrasonic-sensor
 */

//#define TRIG_PIN 22 // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
//#define ECHO_PIN 25 // ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin
//
//float duration_us, distance_cm;
//
//void setup() {
//  // begin serial port
//  Serial.begin (9600);
//
//  // configure the trigger pin to output mode
//  pinMode(TRIG_PIN, OUTPUT);
//  // configure the echo pin to input mode
//  pinMode(ECHO_PIN, INPUT);
//}
//
//void loop() {
//  // generate 10-microsecond pulse to TRIG pin
//  digitalWrite(TRIG_PIN, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(TRIG_PIN, LOW);
//
//  // measure duration of pulse from ECHO pin
//  duration_us = pulseIn(ECHO_PIN, HIGH);
//
//  // calculate the distance
//  distance_cm = 0.017 * duration_us;
//
//  // print the value to Serial Monitor
//  Serial.print("distance: ");
//  Serial.print(distance_cm);
//  Serial.println(" cm");
//
//  delay(500);
//}

















/*
  HC-SR04 with Temp and Humidity Demonstration
  HC-SR04-Temp-Humid-Demo.ino
  Demonstrates enhancements of HC-SR04 Ultrasonic Range Finder
  With DHT22 Temperature and Humidity Sensor
  Displays results on Serial Monitor

  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/



// Include NewPing Library
#include "NewPing.h"

// Define Constants


#define TRIGGER_PIN  22
#define ECHO_PIN     25
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


float duration; // Stores HC-SR04 pulse duration value
float distance; // Stores calculated distance in cm
float soundsp=0.034;  // Stores calculated speed of sound in M/S
int iterations = 5;



void setup() {
  Serial.begin (9600);
  
}

void loop()
{

  delay(2000);  // Delay so DHT-22 sensor can stabalize

    


    
  duration = sonar.ping_median(iterations);
  
  // Calculate the distance
  distance = (duration / 2) * soundsp;
  
  // Send results to Serial Monitor
  
    Serial.print("Sound: ");
    Serial.print(soundsp);
    Serial.print(" m/s, ");

    Serial.print("Distance: ");

    Serial.print(distance);
    Serial.print(" cm");
    delay(500);
    
  
  Serial.println(" ");
}
