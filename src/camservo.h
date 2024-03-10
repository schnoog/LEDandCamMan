#ifndef __CAMSERVO
#define __CAMSERVO

#include <Servo.h>



Servo servo1;
Servo servo2;


void setServo1(int degrees){
    servo1.write(degrees);
}
void setServo2(int degrees){
    servo2.write(degrees);
}

void servo_setup() {

    servo1.attach(
        SERVO1_PIN, 
        Servo::CHANNEL_NOT_ATTACHED, 
        45,
        120
    );
    servo1.attach(
        SERVO2_PIN, 
        Servo::CHANNEL_NOT_ATTACHED, 
        45,
        120
    );


}








#endif