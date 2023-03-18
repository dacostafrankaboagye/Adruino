
const int trigPin = 22;
const int echoPin = 25 ;
int wLed = 26;


//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;


// include the library code:
#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);




void setup() {
  Serial.begin(115200);
  
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(wLed, OUTPUT);


  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Distance");
}
 
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  delay(200);
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  if (distanceCm >= 15){
    digitalWrite(wLed, HIGH);
    }

    else digitalWrite(wLed, LOW);  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  lcd.print(distanceCm);
  distanceCm = 0;
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  
  delay(2000);
}
