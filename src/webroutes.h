#ifndef __webroutes
#define __webroutes


#include <web_html.h>
#include <projeeprom.h>
#include <webhandle.h>
#include <camservo.h>


void setup_web_routes(){

    //server.on("/api/data", HTTP_GET, handleDataRequest);
    server.on("/cam/print", HTTP_GET, [](AsyncWebServerRequest *request) {
        restoreFromEEPROM();
        setServo1(CamXPrint);
        setServo2(CamYPrint);
        char responseBuffer[100]; // buffer to hold the response
        snprintf(responseBuffer, sizeof(responseBuffer), "%d,%d", XPos, YPos);
        request->send(200, "text/plain", responseBuffer);

    });

    server.on("/cam/pos", HTTP_GET, [](AsyncWebServerRequest *request) {
        char responseBuffer[100]; // buffer to hold the response
        snprintf(responseBuffer, sizeof(responseBuffer), "%d,%d", XPos, YPos);
        request->send(200, "text/plain", responseBuffer);
    });

    server.on("^\\/cam\\/([0-9]+)\\/([0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String part1 = request->pathArg(0);
        String part2 = request->pathArg(1);
        int XVAL = part1.toInt();
        int YVAL = part2.toInt();

        setServo1(XVAL);
        delay(500);
        setServo2(YVAL);
        char responseBuffer[100]; // buffer to hold the response
        snprintf(responseBuffer, sizeof(responseBuffer), "%d,%d", XPos, YPos);
        request->send(200, "text/plain", responseBuffer);

//        request->send(200, "text/plain", "-calibrate-");
    });


    server.on("^\\/cam\\/printx\\/([0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String newmax = request->pathArg(0);
        int tmp = newmax.toInt();
        CamXPrint = tmp;
        saveToEEPROM();
        request->send(200, "text/plain", "set print x");
    });

    server.on("^\\/cam\\/printy\\/([0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String newmax = request->pathArg(0);
        int tmp = newmax.toInt();
        CamYPrint = tmp;
        saveToEEPROM();
        request->send(200, "text/plain", "set print y");
    });


    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html; charset=utf-8", PAGE_MAIN);
    });

    server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request){
        handleLedColor(request);
    });






}

#endif