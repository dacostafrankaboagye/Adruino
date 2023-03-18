
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "Frank";
const char* password = "goodwill";

WebServer server(80);

const int led = 2;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}


/*
//int led1  = 25;
//int led2 = 26;
//
//void setup(){
//  pinMode(led1,OUTPUT);
//  pinMode(led2,OUTPUT);
//}
//
//void loop(){
//  digitalWrite(led1, HIGH);
//  digitalWrite(led2, LOW);
//  delay(1000);
//  digitalWrite(led2, HIGH);
//  digitalWrite(led1, LOW);
//  delay(1000);
//}


//------------------ GPIO INTERRUPS
/*

#include <Arduino.h>

struct Button {
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    bool pressed;
};

//Button button1 = {23, 0, false};
Button button1 = {18, 0, false};

//void ARDUINO_ISR_ATTR isr(void* arg) {
//    Button* s = static_cast<Button*>(arg);
//    s->numberKeyPresses += 1;
//    s->pressed = true;
//}

// not checking for bounce
//void IRAM_ATTR isr() {
//    button1.numberKeyPresses++;
//    button1.pressed = true;
//}

// to debounce
unsigned long button_time = 0;
unsigned long last_button_time = 0;

void IRAM_ATTR isr(){
  button_time = millis();
  if(button_time - last_button_time > 250){
    button1.numberKeyPresses++;
    button1.pressed = true;
    last_button_time = button_time;
  }
}

void setup() {
    Serial.begin(115200);
    pinMode(button1.PIN, INPUT_PULLUP);
    //attachInterruptArg(button1.PIN, isr, &button1, FALLING);
    //pinMode(button2.PIN, INPUT_PULLUP);
    attachInterrupt(button1.PIN, isr, FALLING);
}

void loop() {
    if (button1.pressed) {
        Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
        button1.pressed = false;
    }
//    if (button2.pressed) {
//        Serial.printf("Button 2 has been pressed %u times\n", button2.numberKeyPresses);
//        button2.pressed = false;
//    }
//    static uint32_t lastMillis = 0;
//    if (millis() - lastMillis > 10000) {
//      lastMillis = millis();
//      detachInterrupt(button1.PIN);
//    }
}

*/






//_______ timer wake up
