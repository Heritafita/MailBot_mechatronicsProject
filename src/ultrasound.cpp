#include "ultrasound.h"
#include "Arduino.h"

// int TRIG1 =33;
// int ECHO1 =25;
// int TRIG2 =34;
// int ECHO2 =35;


int TRIG1 =25;
int ECHO1 =35;
int TRIG2 =13;
int ECHO2 =12;

float duration_1;
float duration_2;




void init_untrasounds(){
pinMode(TRIG1, OUTPUT);
pinMode(ECHO1, INPUT);
pinMode(TRIG2, OUTPUT);
pinMode(ECHO2, INPUT);
}

void switch_ultrasounds(){
    // first sensor
digitalWrite(TRIG1, LOW);
delayMicroseconds(2);
digitalWrite(TRIG1, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG1, LOW);
duration_1 = pulseIn(ECHO1, HIGH);
// second sensor
// digitalWrite(TRIG2, LOW);
// delayMicroseconds(2);
// digitalWrite(TRIG2, HIGH);
// delayMicroseconds(10);
// digitalWrite(TRIG2, LOW);
// duration_2 = pulseIn(ECHO2, HIGH);
};
float read_ultrasound1(){
   return (duration_1 * 0.034 / 2);
};
float read_ultrasound2(){
    return (duration_2 * 0.034 / 2);
};