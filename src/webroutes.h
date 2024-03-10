#ifndef __webroutes
#define __webroutes


#include <web_html.h>

#include <webhandle.h>



void setup_web_routes(){

    //server.on("/api/data", HTTP_GET, handleDataRequest);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html; charset=utf-8", PAGE_MAIN);
    });

    server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request){
        handleLedColor(request);
    });

    server.on("/a", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html; charset=utf-8", "Hi! This is ElegantOTA Demo. <br> find the updater here <a href='/update'>elegantota</a>  ");
    });

    server.on("/hia", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html; charset=utf-8", "HUHU<hr>! This is ElegantOTA Demo. <br> find the updater here <a href='/update'>elegantota</a>  ");
    });

    server.on("/api/autocontrol", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", "/api/autocontrol");
    });

    server.on("/api/mancontrol", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", "/api/mancontrol");
    });

    server.on("/api/pumps/1", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", "/api/pumps/1");
    });    

    server.on("/api/pumps/0", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", "/api/pumps/0");
    });    

    server.on("^\\/api\\/tare\\/([0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String newmax = request->pathArg(0);
        int balance = newmax.toInt();
        request->send(200, "text/plain", "-tare-");
    });

    server.on("^\\/api\\/calibrate\\/([0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String newmax = request->pathArg(0);
        int balance = newmax.toInt();
        request->send(200, "text/plain", "-calibrate-");
    });


    server.on("^\\/api\\/maxhum\\/([0-9]+(\\.[0-9]+)?)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String newmax = request->pathArg(0);
//        MaxHum = newmax.toFloat();
//        save_HumSettings();
        request->send(200, "text/plain", "-maxhum-");
    });

    server.on("^\\/api\\/minhum\\/([0-9]+(\\.[0-9]+)?)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String newmax = request->pathArg(0);
//        MinHum = newmax.toFloat();
//        save_HumSettings();
        request->send(200, "text/plain", "-minhum-");
    });

    
    server.on("^\\/api\\/emptyspool\\/([0-9]+)\\/([0-9]+)$", HTTP_GET, [](AsyncWebServerRequest *request) {
        String balStr = request->pathArg(0); // Extract <Balance> from the URL
        String eswStr = request->pathArg(1); // Extract <Weight> from the URL

        // Convert the extracted strings to integers
        int bal = balStr.toInt();
        int esw = eswStr.toInt();
//        EmptySpool[bal -1] = esw;
//        SaveSpoolTaras();
        // Now you can use bal and esw as integers in your code

        // Example response
        request->send(200, "text/plain", "Balance: " + String(bal) + ", Weight: " + String(esw));
    });





}

#endif