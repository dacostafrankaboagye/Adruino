//
//#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
//#define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */
//
//RTC_DATA_ATTR int bootCount = 0;
//
//
//void print_wakeup_reason(){
//  esp_sleep_wakeup_cause_t wakeup_reason;
//
//  wakeup_reason = esp_sleep_get_wakeup_cause();
//
//  switch(wakeup_reason)
//  {
//    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
//    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
//    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
//    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
//    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
//    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
//  }
//}
//
//void setup(){
//  Serial.begin(115200);
//  delay(1000); //Take some time to open up the Serial Monitor
//
//  //Increment boot number and print it every reboot
//  ++bootCount;
//  Serial.println("Boot number: " + String(bootCount));
//
//  //Print the wakeup reason for ESP32
//  print_wakeup_reason();
//
//
//  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
//  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
//  " Seconds");
//
//  Serial.println("Going to sleep now");
//  Serial.flush(); 
//  esp_deep_sleep_start();
//  Serial.println("This will never be printed");
//}
//
//void loop(){
//  //This is not going to be called
//}


//____________



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

/*
const char* ca = \ 
"-----BEGIN CERTIFICATE-----\n" \  
"MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/\n" \  
"MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \  
"DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow\n" \  
"SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT\n" \  
"GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC\n" \  
"AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF\n" \  
"q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8\n" \  
"SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0\n" \  
"Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA\n" \  
"a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj\n" \  
"/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T\n" \  
"AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG\n" \  
"CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv\n" \  
"bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k\n" \  
"c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw\n" \  
"VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC\n" \  
"ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz\n" \  
"MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu\n" \  
"Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF\n" \  
"AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo\n" \  
"uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/\n" \  
"wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu\n" \  
"X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG\n" \  
"PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6\n" \  
"KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==\n" \  
"-----END CERTIFICATE-----\n";
*/


float hum;  
float temp; 

//-----------------
String url = String("http://192.168.130.13/sensordata/index.php?temperature=");
// //192.168.43.13/sensordata/index.php?temperature=99&humidity=88&ultrasonic=77
//


void setup() {

    USE_SERIAL.begin(115200);

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

}

void loop() {
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
