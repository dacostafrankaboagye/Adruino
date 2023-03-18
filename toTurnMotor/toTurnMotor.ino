
int motorPin =33;

void setup() {
  // initialize digital pin motorPin as an output.
  pinMode(motor, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

      digitalWrite(motorPin, LOW);    // turn the LED off by making the voltage LOW
  delay(10000);                       // wait for a second

  digitalWrite(motorPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(10000);                       // wait for a second
}
