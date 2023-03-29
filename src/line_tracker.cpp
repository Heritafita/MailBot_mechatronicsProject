#include "line_tracker.h"
#include "Arduino.h"



void init_tracker(){
pinMode(L1, INPUT_PULLDOWN);
pinMode(L2, INPUT_PULLDOWN);
pinMode(L3, INPUT_PULLDOWN);
pinMode(L4, INPUT_PULLDOWN);
pinMode(L5, INPUT_PULLDOWN);
}

int Center(){
   return analogRead(L3);
}
int Left1(){
    return analogRead(L2);
}
int Left2(){
    return analogRead(L1);
}
int Right1(){
    return analogRead(L4);
}
int Right2(){
    return analogRead(L5);
}


void display_tracker(){
// Serial.println("Infrared_values: ");

Serial.print("Left2 : ");
Serial.println(Left2());
// delay (500);
Serial.print("Left1 : ");
Serial.println(Left1());
Serial.print("Center: ");
Serial.println(Center());
// delay (1000);

// delay (500);
Serial.print("Right1 : ");
Serial.println(Right1());
// delay (500);
Serial.print("Right2: ");
Serial.println(Right2());
// Serial.println(" ");
delay (500);
} 
