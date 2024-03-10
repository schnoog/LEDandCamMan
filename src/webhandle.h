
#include <neoled.h>

void handleLedColor(AsyncWebServerRequest *request) {
    Serial.println("Received LED color request");

    // Extract parameters from URL path
    String url = request->url();
    Serial.print("Request URL:");
    Serial.println(url);

    // Find indices of slashes in the URL
    int slashIndex[5]; // Stores the indices of slashes in the URL
    int prevSlashIndex = 0;
    int count = 0;
    while ((slashIndex[count] = url.indexOf('/', prevSlashIndex)) != -1 && count < 4) {
        prevSlashIndex = slashIndex[count++] + 1;
    }
    if (count < 3) {
        Serial.println("Invalid URL format");
        request->send(400, "text/plain", "Invalid URL format");
        return;
    }

    // Extract parameter values from URL path
    int iRED = url.substring(slashIndex[1] + 1, slashIndex[2]).toInt();
    int iGREEN = url.substring(slashIndex[2] + 1, slashIndex[3]).toInt();
    int iBLUE = url.substring(slashIndex[3] + 1).toInt();
    int iBrightness = 255; // Default brightness value

    // Check if brightness parameter is provided
    if (count == 4) {
        iBrightness = url.substring(slashIndex[4] + 1).toInt();
    }

    // Check if values are within the valid range
    if (iRED >= 0 && iRED <= 255 &&
        iGREEN >= 0 && iGREEN <= 255 &&
        iBLUE >= 0 && iBLUE <= 255 &&
        iBrightness >= 0 && iBrightness <= 255) {
        
        // Set LED color
        LED_SetColor(iRED, iGREEN, iBLUE, iBrightness);
        Serial.print("Set led to :");
        Serial.print(iRED);
        Serial.print(",");
        Serial.print(iGREEN);
        Serial.print(",");
        Serial.print(iBLUE);
        Serial.print(",");
        Serial.print(iBrightness);
        Serial.println("");            
//        request->send(200, "text/plain", "LED color set successfully");

        char responseBuffer[100]; // buffer to hold the response

// Format the response with the values of global variables
        snprintf(responseBuffer, sizeof(responseBuffer), "%d,%d,%d,%d", iRED, iGREEN, iBLUE, iBrightness);
        request->send(200, "text/plain", responseBuffer);




        return;
    }

    // If any parameter is missing or invalid, respond with error
    Serial.println("Invalid parameters");
    request->send(400, "text/plain", "Invalid parameters");
}
