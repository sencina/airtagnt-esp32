#include <HardwareSerial.h>
#include <TinyGPSPlus.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h>


TinyGPSPlus gps;

const char* ssid = "encigol";
const char* password = "encigol1";
WiFiMulti wifiMulti;

//Your Domain name with URL path or IP address with path
const char* serverName = "http://airtagnt-server-production.up.railway.app";


int i;

void sendRequest(double lat, double longitude, uint32_t satellites, double hdop){
   Serial.println("Posting JSON data to server...");
  // Block until we are able to connect to the WiFi access point
  if (wifiMulti.run() == WL_CONNECTED) {

    HTTPClient http;

    http.begin("https://airtagnt-server-production.up.railway.app/location");
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> doc;
    // Add values in the document
    //
    doc["lat"] = std::to_string(lat);
    doc["long"] = std::to_string(longitude);
    doc["satellites"] = std::to_string(satellites);
    doc["hdop"] = std::to_string(hdop);


    String requestBody;
    serializeJson(doc, requestBody);

     Serial.println(requestBody);
    int httpResponseCode = http.POST(requestBody);

    if(httpResponseCode>0){

      String response = http.getString();

      Serial.println(httpResponseCode);
      Serial.println(response);

    }


  }
}

void displayInfo() {
    i++;
  Serial.print(F("\nLocation: "));
  if (gps.location.isValid()){
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    if(i % 20 == 0) sendRequest(gps.location.lat(), gps.location.lng(), gps.satellites.value(), gps.hdop.value());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
}

void updateSerial(){
  delay(500);
  while (Serial.available())  {
    Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (Serial2.available())  {
    Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
  }
// while (Serial2.available())  {
//     gps.encode(Serial2.read());//Forward what Software Serial received to Serial Port
//     displayInfo();
//   }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);

  i = 0;
delay(4000);
  wifiMulti.addAP(ssid, password);


}

void loop() {
    // updateSerial();
    // delay(10000);

    //updateSerial();
    if(Serial2.available() > 0){
    //delay(5000);
    if (gps.encode(Serial2.read()))
      displayInfo();
    }
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }
}