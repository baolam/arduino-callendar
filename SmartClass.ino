#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include <Ethernet.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define DEBUG
#include "Callendar.h"

#define CHIP_SELECT 4
#define ADDRESS_3231 0x27
#define ISD1820 5
#define DHTPIN 7
#define DHTTYPE 11

byte mac[] = {};
const char* host = "";
const int port = 80;
const char* appurl = "";
const char* appjson = "";

IPAddress ip(192, 168, 1, 20);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
Callendar callendar;
EthernetClient client;
HttpClient http(client, host, port);
DHT dht(DHTPIN, DHTTYPE);
File file;

void readJson(const char* url);
int convertBintoDec(String data);

void setup() {
  // put your setup code here, to run once:
  if(! SD.begin(CHIP_SELECT)) {
    
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

void readJson(const char* url) {
  file = SD.open(url);
  String dt;
  if(file) {
    if(file.available()) {
      dt = file.read();
    }
  }  

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, dt);

  if(error) {
    return;
  }

  JsonObject obj = doc.as<JsonObject>();
}
