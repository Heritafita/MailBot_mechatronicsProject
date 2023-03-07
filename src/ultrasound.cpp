#include "ultrasound.h"
#include "Arduino.h"

// int TRIG1 =33;
// int ECHO1 =25;
// int TRIG2 =34;
// int ECHO2 =35;


#define TRIG_PIN_1 2
#define ECHO_PIN_1 15
#define TRIG_PIN_2 18
#define ECHO_PIN_2 19

long duration_1, distance_1;
long duration_2, distance_2;




void init_untrasounds(){
pinMode(TRIG_PIN_1, OUTPUT);
pinMode(ECHO_PIN_1, INPUT);
pinMode(TRIG_PIN_2, OUTPUT);
pinMode(ECHO_PIN_2, INPUT);
}

void switch_ultrasounds(){
    // first sensor
digitalWrite(TRIG_PIN_1, LOW);
delayMicroseconds(2);
digitalWrite(TRIG_PIN_1, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN_1, LOW);
duration_1 = pulseIn(ECHO_PIN_1, HIGH);
distance_1 = duration_1 * 0.034 / 2;

delay(10);

// second sensor
digitalWrite(TRIG_PIN_2, LOW);
delayMicroseconds(2);
digitalWrite(TRIG_PIN_2, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN_2, LOW);
duration_2 = pulseIn(ECHO_PIN_2, HIGH);
distance_2 = duration_2 * 0.034 / 2;
// second sensor
// digitalWrite(TRIG2, LOW);
// delayMicroseconds(2);
// digitalWrite(TRIG2, HIGH);
// delayMicroseconds(10);
// digitalWrite(TRIG2, LOW);
// duration_2 = pulseIn(ECHO2, HIGH);
};
float read_ultrasound1(){
   return distance_1;
};
float read_ultrasound2(){
    return distance_2;
};

void display_distances(){
Serial.print("Sensor 1: ");
Serial.print(read_ultrasound1());
Serial.print(" cm\t");
Serial.print("Sensor 2: ");
Serial.print(read_ultrasound2());
Serial.println(" cm"); 
}