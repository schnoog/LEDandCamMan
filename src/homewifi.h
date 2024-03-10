#pragma once


#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>
#include <credentials.h>

String hostname = "3DCamControl";


WiFiClient espClient;
AsyncWebServer server(80);

unsigned long previousMillis = 0;
unsigned long interval = 30000;
unsigned long ota_progress_millis = 0;

#include <webroutes.h>


void onOTAStart() {
  // Log when OTA has started
  Serial.println("OTA update started!");
  // <Add your own code here>
}

void onOTAProgress(size_t current, size_t final) {
  // Log every 1 second
  if (millis() - ota_progress_millis > 1000) {
    ota_progress_millis = millis();
    Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
  }
}

void onOTAEnd(bool success) {
  // Log when OTA has finished
  if (success) {
    Serial.println("OTA update finished successfully!");
  } else {
    Serial.println("There was an error during OTA update!");
  }
  // <Add your own code here>
}



void ota_setup(){
//AsyncWebServerRequest 
//    server.on("/", []() {
//        server.send(200, "text/plain", "Hi! This is ElegantOTA Demo. <br> find the updater here <a href='/update'>elegantota</a>  ");
//    });

  //server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  //  request->send(200, "text/html; charset=utf-8", "Hi! This is ElegantOTA Demo. <br> find the updater here <a href='/update'>elegantota</a>  ");
  //});
  setup_web_routes();
  server.on("/hi", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html; charset=utf-8", "HUHU<hr>! This is ElegantOTA Demo. <br> find the updater here <a href='/update'>elegantota</a>  ");
  });


  ElegantOTA.begin(&server);    // Start ElegantOTA
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);
  server.begin();
  Serial.println("HTTP server started");
}

void ota_loop(){
    ElegantOTA.loop();
}


void wifi_setup(){
    WiFi.mode(WIFI_STA); //Optional
//    WiFi.setHostname(hostname.c_str()); //define hostnameb
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    ota_setup();
}

long loopRet = 0;

void wifi_loop(){

  loopRet++;
  if(loopRet > 90000000){
    loopRet = 0;
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
  }

  int wifi_retry = 0;
  while(WiFi.status() != WL_CONNECTED && wifi_retry < 5 ) {
      wifi_retry++;
      Serial.println("WiFi not connected. Try to reconnect");
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid,password);
      delay(100);
  }
  if(wifi_retry >= 5) {
      Serial.println("\nReboot");
      ESP.restart();
  }


    ota_loop();

}


