#include <Servo.h>

static const int servoPin = 12;  // defines pin number for PWM

Servo servo1;  // Create object for servo motor

void setup() {
Serial.begin(115200);
servo1.attach(servoPin);  // start the library 
}

void loop() {
for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
servo1.write(posDegrees);
Serial.println(posDegrees);
delay(20);
}

for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
servo1.write(posDegrees);
Serial.println(posDegrees);
delay(20);
}
}
