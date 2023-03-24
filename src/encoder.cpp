
#include "encoder.h"
#include "Arduino.h"
double position=0;
static uint32_t oldtime=millis();

int Right_ENC_CHAN_A = 35;  // conne
int Right_ENC_CHAN_B= 36; 
int Left_ENC_CHAN_A = 22; 
int Left_ENC_CHAN_B = 39; // soudé à 23 au niveau hard 

double Left_ENC_CHAN_A_Ticks = 0;
double Left_ENC_CHAN_B_Ticks = 0;
double Right_ENC_CHAN_A_Ticks = 0;
double Right_ENC_CHAN_B_Ticks = 0;

void Init_Encoders(){
  pinMode(Left_ENC_CHAN_A,INPUT_PULLUP);
  pinMode(Left_ENC_CHAN_B,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(Right_ENC_CHAN_A), SwitchRightEncoderA, RISING);
  attachInterrupt(digitalPinToInterrupt(Right_ENC_CHAN_B), SwitchRightEncoderB, RISING);

  attachInterrupt(digitalPinToInterrupt(Left_ENC_CHAN_A), SwitchLeftEncoderA, RISING);
  attachInterrupt(digitalPinToInterrupt(Left_ENC_CHAN_B), SwitchLeftEncoderB, RISING);
}

void SwitchRightEncoderA(){
   Right_ENC_CHAN_A_Ticks++;   
}
void SwitchRightEncoderB(){  
   Right_ENC_CHAN_B_Ticks++;
}
void SwitchLeftEncoderA(){
   Left_ENC_CHAN_A_Ticks++;
}
void SwitchLeftEncoderB(){
   Left_ENC_CHAN_B_Ticks++;
}

double Read_Right_ENC_CHAN_A(){
  return Right_ENC_CHAN_A_Ticks; 
  
}
double Read_Right_ENC_CHAN_B(){
  return Right_ENC_CHAN_B_Ticks; 
}

double Read_Left_ENC_CHAN_A(){
  return Left_ENC_CHAN_A_Ticks; 
}

double Read_Left_ENC_CHAN_B(){
  return Left_ENC_CHAN_B_Ticks; 
}

void display_encoders(){
if ( (millis()-oldtime) > 2000) {
    oldtime = millis();
    Serial.println("Right_ENC_CHAN_A : ");
    Serial.println(Read_Right_ENC_CHAN_A());
    // delay (50);
    // Serial.println("Right_ENC_CHAN_B : ");
    // Serial.println(Read_Right_ENC_CHAN_B());
    // delay (50);
    Serial.println("Left_ENC_CHAN_A : ");
    Serial.println(Read_Left_ENC_CHAN_A());
    // delay (50);
    // Serial.println("Left_ENC_CHAN_B : ");
    // Serial.println(Read_Left_ENC_CHAN_B());
    // Serial.println("Traveled_Distance (m): ");
    // Serial.println(traveled_distance());
    // delay (1000);
}

} 

double traveled_distance(){
int ticks_per_round = 228; // datasheet
double tyre_radius = (65/2)/1000;
double N = Read_Right_ENC_CHAN_A();
double round_count = N/ticks_per_round;
// double angular_speed = (2*3.141592*round_count)/1; // rad/s
// N = 0;
position = (2*3.141592 * tyre_radius)* round_count; // m
// double linear_speed = tyre_radius*angular_speed; // m/s
return position;
}

