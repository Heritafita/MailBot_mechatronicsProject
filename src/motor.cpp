
#include "motor.h"
#include "Arduino.h"

#define enA  14
#define in1  27
#define in2  26

// Motor B, Right
 
#define enB  32
#define in3  16
#define in4  33

void init_motors(){
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Turn off motors - Initial state
  stop_motors();
}

void move_forward(int pwmA, int pwmB){
int speedA = pwmA;
int speedB = pwmB;
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enA, speedA);
analogWrite(enB, speedB);
}

void move_backward(int pwmA, int pwmB){
int speedA = pwmA;
int speedB = pwmB;
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enA, speedA);
analogWrite(enB, speedB);
}

void stop_motors(){
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
}

