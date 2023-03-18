//
//#include <IRremote.h>
//
//#define first_key 6553
//#define second_key 65535
//#define third_key 6535
//#define fourth_key 653
//int receiver_pin = 8;
//
//int first_led_pin = 7;
//int second_led_pin = 6; // a seond...
//int third_led_pin = 5;
//int fourth_led_pin = 4;
//int led[] = {0,0,0,0};
//IRrecv receiver(receiver_pin);
//decode_results output;
//
//void setup()
//{
//Serial.begin(9600);
//receiver.enableIRIn();
//pinMode(first_led_pin, OUTPUT);
//pinMode(second_led_pin, OUTPUT);
//pinMode(third_led_pin, OUTPUT);
//pinMode(fourth_led_pin, OUTPUT);
//}
//
//void loop() {
//if (receiver.decode(&output)) {
//unsigned int value = output.value;
//switch(value) {
//case first_key:
//if(led[1] == 1) {
//digitalWrite(first_led_pin, LOW);
//led[1] = 0;
//} else {
//digitalWrite(first_led_pin, HIGH);
//led[1] = 1;
//}
//break;
//case second_key:
//
//if(led[2] == 1) {
//digitalWrite(second_led_pin, LOW);
//led[2] = 0;
//} else {
//digitalWrite(second_led_pin, HIGH);
//led[2] = 1;
//}
//break;
//case third_key:
//
//if(led[3] == 1) {
//digitalWrite(third_led_pin, LOW);
//led[3] = 0;
//} else {
//digitalWrite(third_led_pin, HIGH);
//led[3] = 1;
//}
//break;
//case fourth_key:
//
//if(led[4] == 1) {
//digitalWrite(fourth_led_pin, LOW);
//led[4] = 0;
//} else {
//digitalWrite(fourth_led_pin, HIGH);
//led[4] = 1;
//}
//break;
//}
//Serial.println(value);
//receiver.resume();
//}
//}
//


//
#include <IRremote.h>

const int recvPin = 4;

const int redPin = 8;
const int yellowPin = 7;

int togglestate = 0;

IRrecv irrecv(recvPin);
decode_results results;


void setup(){
  
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(redPin, OUTPUT);
  
  pinMode(yellowPin, OUTPUT);
}

void loop(){
  if(irrecv.decode(&results)){

    switch(results.value){
      case 16720605:
      digitalWrite(redPin,HIGH);
      delay(2000);
      digitalWrite(redPin,LOW);
      break;
      case 16736925:
      if(togglestate==0){
        digitalWrite(yellowPin,HIGH);
        Serial.println(results.value);
        togglestate = 1;
      }
      else{
        Serial.println("--");
        Serial.println(results.value);
        digitalWrite(yellowPin,LOW);
        togglestate=0;
      }
      break;
      
    }
    Serial.println('other');
   
    irrecv.resume();
         
    }
    
    
  }
//    Serial.println(results.value, HEX);
//    irrecv.resume();
