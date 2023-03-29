
#include "motor.h"
#include "Arduino.h"
#include "encoder.h"

#define pwm1  14
#define dir1  27
// #define in2  26

// Motor B, Right
 
#define pwm2  13
#define dir2  34
// #define in4  35
// #define in4  23
 #define relay  23
int move = 10;

void init_motors(){
  // Set all the motor control pins to outputs
  //  delay(500);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(dir1, OUTPUT);
  // pinMode(in2, OUTPUT);
  pinMode(dir2, OUTPUT);
  // pinMode(relay, OUTPUT);
 
  // digitalWrite(relay, HIGH);
  // pinMode(in4, OUTPUT);
  // move off motors - Initial state
  stop_motors();
}

void move_forward(int pwmA, int pwmB){
int speedA = pwmA;
int speedB = pwmB;
digitalWrite(dir1, LOW);
// digitalWrite(in2, LOW);
digitalWrite(dir2, LOW);
// digitalWrite(in4, HIGH);
analogWrite(pwm1, speedA);
analogWrite(pwm2, speedB);
}

void move_backward(int pwmA, int pwmB){
int speedA = pwmA;
int speedB = pwmB;
digitalWrite(dir1, HIGH);
// digitalWrite(in2, HIGH);
digitalWrite(dir2, HIGH);
// digitalWrite(in4, LOW);
analogWrite(pwm1, speedA);
analogWrite(pwm2, speedB);
}

void move_right(int pwmA, int pwmB){
int speedA = pwmA-move;
int speedB = pwmB;
digitalWrite(dir1, LOW);
// digitalWrite(in2, LOW);
digitalWrite(dir2, LOW);
// digitalWrite(in4, HIGH);
analogWrite(pwm1, speedA);
analogWrite(pwm2, speedB);

}

void move_left(int pwmA, int pwmB){
int speedA = pwmA;
int speedB = pwmB-move;
digitalWrite(dir1, LOW);
// digitalWrite(in2, LOW);
digitalWrite(dir2, LOW);
// digitalWrite(in4, HIGH);
analogWrite(pwm1, speedA);
analogWrite(pwm2, speedB);
}

void stop_motors(){
analogWrite(pwm1, 0);
analogWrite(pwm2, 0);
// digitalWrite(dir1, LOW);
// digitalWrite(in2, LOW);
// digitalWrite(dir2, LOW);
// digitalWrite(in4, LOW);
}

