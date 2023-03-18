
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include <DHT.h>;

#define DHTPIN 23   
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE); 

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  8        /* Time ESP32 will go to sleep (in seconds) */
// change 8 to 5

RTC_DATA_ATTR int bootCount = 0;


void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}


float hum;  
float temp; 

//-----------------
RTC_DATA_ATTR String url = String("http://192.168.130.13/sensordata/index.php?temperature=");
// //192.168.43.13/sensordata/index.php?temperature=99&humidity=88&ultrasonic=77
//


void perform(){
    delay(2000);
    hum = dht.readHumidity();
  temp= dht.readTemperature();
   USE_SERIAL.println("Humidity: ");
   USE_SERIAL.println(hum);
   USE_SERIAL.println(" %, Temp: ");
   USE_SERIAL.println(temp);
   USE_SERIAL.println(" Celsius");

       url = url+ temp;
    url = url + String("&humidity=");
    url = url+hum;
    url = url + String("&ultrasonic=00");

    USE_SERIAL.println(" ");
    USE_SERIAL.println(url);
    USE_SERIAL.println(" ");

     // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        // http.begin("http://example.com/index.html"); //HTTP
        http.begin(url); //HTTP


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
  url = String("http://192.168.130.13/sensordata/index.php?temperature=");
    delay(5000);
}


void setup(){
  Serial.begin(115200);
  delay(1000); //Take some time to open up the Serial Monitor

      dht.begin();

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

        for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("Frank", "goodwill");
    
  //Increment boot number and print it every reboot
  ++bootCount;
  USE_SERIAL.println(" ");
  Serial.println("Boot number: " + String(bootCount));
  USE_SERIAL.println(" ");
  
  //Print the wakeup reason for ESP32
  print_wakeup_reason();


  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");

  perform();


}

void loop(){
  //This is not going to be called

    Serial.println("Going to sleep now");
  Serial.flush(); 
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
  
}


//____________


//
//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WebServer.h>
//#include <ESPmDNS.h>
//
//#include <DHT.h>;
//
//#define DHTPIN 23   
//#define DHTTYPE DHT22   
//DHT dht(DHTPIN, DHTTYPE); 
//
//float hum;  
//float temp; 
//
//const char* ssid = "Frank";
//const char* password = "goodwill";
//
//WebServer server(80);
//
//const int led = 2;
//
//void handleRoot() {
//  digitalWrite(led, 1);
//  server.send(200, "text/plain", "hello from esp32!");
//  digitalWrite(led, 0);
//}
//
//void handleSensorData() {
//  digitalWrite(led, 1);
//   hum = dht.readHumidity();
//   temp= dht.readTemperature();
//   String msg = "Temperature reading = ";
//   msg = msg + temp;
//   msg = msg + " & Humidity reading = ";
//   msg = msg + hum;
//  server.send(200, "text/plain",msg);
//  digitalWrite(led, 0);
//}
//
//
//void handleNotFound() {
//  digitalWrite(led, 1);
//  String message = "File Not Found\n\n";
//  message += "URI: ";
//  message += server.uri();
//  message += "\nMethod: ";
//  message += (server.method() == HTTP_GET) ? "GET" : "POST";
//  message += "\nArguments: ";
//  message += server.args();
//  message += "\n";
//  for (uint8_t i = 0; i < server.args(); i++) {
//    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
//  }
//  server.send(404, "text/plain", message);
//  digitalWrite(led, 0);
//}
//
//void setup(void) {
//  dht.begin();
//  
//  pinMode(led, OUTPUT);
//  digitalWrite(led, 0);
//  Serial.begin(115200);
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, password);
//  Serial.println("");
//
//  // Wait for connection
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.print("Connected to ");
//  Serial.println(ssid);
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());
//
//  if (MDNS.begin("esp32")) {
//    Serial.println("MDNS responder started");
//  }
//
//  server.on("/", handleRoot);
//
//  server.on("/inline", []() {
//    server.send(200, "text/plain", "this works as well");
//  });
//
//// .......
//  server.on("/sensorData",handleSensorData);
//
//  server.onNotFound(handleNotFound);
//
//  server.begin();
//  Serial.println("HTTP server started");
//}
//
//void loop(void) {
//  server.handleClient();
//  delay(2);//allow the cpu to switch to other tasks
//}
