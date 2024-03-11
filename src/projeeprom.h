#ifndef __PEP
#define __PEP


#include <EEPROM.h>
#include <camservo.h>

// Define addresses for storing each variable in EEPROM
const int ADDR_Max1 = 0;
const int ADDR_Max2 = ADDR_Max1 + sizeof(int);
const int ADDR_Min1 = ADDR_Max2 + sizeof(int);
const int ADDR_Min2 = ADDR_Min1 + sizeof(int);
const int ADDR_X_PRINT = ADDR_Min2 + sizeof(int);
const int ADDR_Y_PRINT = ADDR_X_PRINT + sizeof(int);


// Function to save variables to EEPROM
void saveToEEPROM() {
    EEPROM.put(ADDR_Max1, Max1);
    EEPROM.put(ADDR_Max2, Max2);
    EEPROM.put(ADDR_Min1, Min1);
    EEPROM.put(ADDR_Min2, Min2);
    EEPROM.put(ADDR_X_PRINT,CamXPrint);
    EEPROM.put(ADDR_Y_PRINT,CamYPrint);
    EEPROM.commit();
}

// Function to restore variables from EEPROM
void restoreFromEEPROM() {
    EEPROM.get(ADDR_Max1, Max1);
    EEPROM.get(ADDR_Max2, Max2);
    EEPROM.get(ADDR_Min1, Min1);
    EEPROM.get(ADDR_Min2, Min2);
    EEPROM.get(ADDR_X_PRINT,CamXPrint);
    EEPROM.get(ADDR_Y_PRINT,CamYPrint);    
}


#endif