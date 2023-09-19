/*
 * Homeschool Robotics University
 * You are allowed to use, make changes and rdestribute the software programs 
 * to as many people as you would love to share to. Authur Samuel Githeri Github handle @alpha466
 * For More Amazing Software Applications... Visit www.hru.co.ke
 * */


#include <ESP8266WiFi.h>// WiFi Liblary 
#include <ESPAsyncTCP.h>// ASPAAsync TCP Liblary
#include <ESPAsyncWebServer.h>// ASPAsync TCP Server 
#include <LittleFS.h>// Littlefs Liblary 
#include <FS.h>// FS Liblary
#include <Wire.h>// Wire Liblary

// Application Software Configaration Settings
#ifndef APSSID
#define APSSID "Horouni"
#define APPSK "12345678"
#endif
const char *ssid = APSSID;// Name of Access Network
const char *password = APPSK;// Password of Access Network
String localHost = "www.hru.co.ke";

//Initialize Digital Pins
const int leftForward = REPLACE_WITH_GPIO;
const int leftBackward = REPLACE_WITH_GPIO;
const int rightForward = REPLACE_WITH_GPIO;
const int rightBackward = REPLACE_WITH_GPIO;

void setup() {
  // set control pins as Output
  pinMode(leftForward,OUTPUT);
  pinMode(leftBackward,OUTPUT);
  pinMode(rightForward,OUTPUT);
  pinMode(rightBackward,OUTPUT);
  //Set outputs to low
  digitalWrite(leftForward,LOW);
  digitalWrite(leftBackward,LOW);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightBackward,LOW);

  //Local host Address
  WiFi.hostname(localHost.c_str());
  //Start Software Access Network
  WiFi.softAP(ssid, password);
  
  delay(2000);

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }


  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to go forward
  server.on("/forward", HTTP_GET, [](AsyncWebServerRequest *request){
    // run forward
    digitalWrite(leftForward,HIGH);
    digitalWrite(leftBackward,LOW);
    digitalWrite(rightForward,HIGH);
    digitalWrite(rightBackward,LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to go forward
  server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request){
    // run left
    digitalWrite(leftForward,LOW);
    digitalWrite(leftBackward,LOW);
    digitalWrite(rightForward,HIGH);
    digitalWrite(rightBackward,LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to go forward
  server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request){
    // run forward
    digitalWrite(leftForward,HIGH);
    digitalWrite(leftBackward,LOW);
    digitalWrite(rightForward,LOW);
    digitalWrite(rightBackward,LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to go forward
  server.on("/reverse", HTTP_GET, [](AsyncWebServerRequest *request){
    // run backward
    digitalWrite(leftForward,LOW);
    digitalWrite(leftBackward,HIGH);
    digitalWrite(rightForward,LOW);
    digitalWrite(rightBackward,HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();

}

void loop() {
  //Lets Create Something Amazing!

}
