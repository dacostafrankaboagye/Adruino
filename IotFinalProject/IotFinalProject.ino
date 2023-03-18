
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>  //because of HTTPClient use
#include "htmltext.h"
#define USE_SERIAL Serial






WiFiMulti wifiMulti;
const char* ssid = "Ben.Fra.Pri";
const char* password = "M633SFTK";







//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

const int led = 2;
const int motorPin = 3;
const int trigPin = 4;
const int echoPin = 5;

WebServer server(80);


void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}


//void handleYaw() {
// 
//  server.send(200, "text/html", page);
//  
//}

void handleUltrasonic(){
  String theData = String(distanceCm);

  String mssg = "Motor is On";
  mssg += theData;
  server.send(200, "text/plain", mssg);
  
}

void handlePush(){
  doGETRequest();
}

void handleStartMotor(){
  Serial.println("motor started");
}

void handleStopMotor(){
  Serial.println("motor stopped");
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
  pinMode(motorPin, OUTPUT);
  digitalWrite(led, 0);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  wifiMulti.addAP("SSID", "PASSWORD");
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {    //multicast DNS service
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/startfan", handleStartMotor);
  server.on("/stopfan", handleStopMotor);
  
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");

}

//String url = String("http://192.168.80.13/sensorproject/toinsert.php?level=");

void perform(){
    delay(2000);
    url = url+ String(distanceCm);
    url = url + String("&cid=2");

    USE_SERIAL.println(" ");
    USE_SERIAL.println(" ");

     // wait for WiFi connection
    while((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http.begin("http://example.com/index.html"); //HTTP
        //http.begin(url);


        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
  //url = String("http://192.168.80.13/sensorproject/toinsert.php?level=");
    delay(5000);
}



void operation(){

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
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  
  delay(2000);
}

void loop(void) {
  server.handleClient();

  
  delay(2);//allow the cpu to switch to other tasks

  
}
       

void doGETRequest(){
  //Check WiFi connection status
  
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;      
      String serverPath = "";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());  //alt use char host[] = "example.com";
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.println("-----===------====+++");
        Serial.println(serverPath);
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        server.send(200, "text/html", payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}
