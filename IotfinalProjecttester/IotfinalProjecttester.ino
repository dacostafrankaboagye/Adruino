#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <WiFiMulti.h>
#include <HTTPClient.h>  //because of HTTPClient use
#include "htmltext.h"
#define USE_SERIAL Serial

const char* ssid = "Ben.Fra.Pri";
const char* password = "M633SFTK";



WiFiMulti wifiMulti;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;


const int motorPin = 3;
const int trigPin = 4;
const int echoPin = 5;

unsigned long current = 0;
unsigned long previous = 0;
const int interval = 1000;


WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}

void handleUltrasonic(){
  //String theData = String(distanceCm);

  String mssg = "Motor is On";
  //mssg += theData;
  server.send(200, "text/plain", mssg);
  
}

void handleStartMotor(){
  Serial.println("motor started");
  // turn on motor
}

void handleStopMotor(){
  Serial.println("motor stopped");
  // turn off motor
}

void handleIot() {
  server.send(200, "text/html", page); 
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

void doGETRequest(){
  //Check WiFi connection status
  
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;      
      String serverPath = "http://example.com/index.html";
      
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
  server.on("/startfan", handleStartMotor);
  server.on("/stopfan", handleStopMotor);
  server.on("/iot", handleIot);

  server.on("/doRq", doGETRequest);
  

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
  Serial.println("working...loop is running...");
}
