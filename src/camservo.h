#ifndef __CAMSERVO
#define __CAMSERVO

#include <Servo.h>



Servo servo1;
Servo servo2;
const int frequency = 50; // Hz

int CamXPrint = 85;
int CamYPrint = 95;
int XPos = 0;
int YPos = 0;

//#define __OW
#ifndef __OW
int Max1 = 150;
int Max2 = 140;
int Min1 = 50;
int Min2 = 50;
#else

int Max1 = 180;
int Max2 = 180;
int Min1 = 0;
int Min2 = 0;

#endif

#include <projeeprom.h>

void setServo1(int degrees){
    if(degrees > Max1) degrees = Max1;
    if(degrees < Min1) degrees = Min1;
    XPos = degrees;
    servo1.write(degrees);
}
void setServo2(int degrees){
    if(degrees > Max2) degrees = Max2;
    if(degrees < Min2) degrees = Min2;    
    YPos = degrees;
    servo2.write(degrees);
}

void servo_setup() {

    servo2.attach(
        SERVO1_PIN, 
        Servo::CHANNEL_NOT_ATTACHED, 
        0,
        180, 
        Servo::DEFAULT_MIN_PULSE_WIDTH_US, 
        Servo::DEFAULT_MAX_PULSE_WIDTH_US, 
        frequency
    );
    servo1.attach(
        SERVO2_PIN, 
        Servo::CHANNEL_NOT_ATTACHED, 
        0,
        180, 
        Servo::DEFAULT_MIN_PULSE_WIDTH_US, 
        Servo::DEFAULT_MAX_PULSE_WIDTH_US, 
        frequency
    );
    restoreFromEEPROM();
setServo1(CamXPrint);
setServo2(CamYPrint);

}








#endif