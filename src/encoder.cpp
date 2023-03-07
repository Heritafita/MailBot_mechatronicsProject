// #define Right_ENC_D 13
// //#define Right_ENC_A A0
// #define Left_ENC_D 12
// //#define Left_ENC_A A3
// float _LeftEncoderTicks = 0;
// float _RightEncoderTicks = 0;
// int forward = 1;
// int backward = 0;
// void setup() {
//   // put your setup code here, to run once:
//   // Encoder
//   Serial.begin(115200);
//   pinMode(Right_ENC_D,INPUT_PULLUP);
// //  pinMode(Right_ENC_A,INPUT_PULLUP);
//   attachInterrupt(digitalPinToInterrupt(Right_ENC_D), readRightEncoder, RISING);
//   pinMode(Left_ENC_D,INPUT_PULLUP);
//  // pinMode(Left_ENC_A,INPUT_PULLUP);
//   attachInterrupt(digitalPinToInterrupt(Left_ENC_D), readLeftEncoder, RISING);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   Serial.print("Encodeur gauche: ");
//   Serial.println(_LeftEncoderTicks);
//   delay(250);
//   Serial.print("Encodeur droite: ");
//   Serial.println(_RightEncoderTicks);
   
// }
// void readRightEncoder(){
//    //(digitalRead(Right_ENC_A)>0) ? (_RightEncoderTicks--) : (_RightEncoderTicks++);
//    _RightEncoderTicks++;   
// }
// void readLeftEncoder(){
//    //(digitalRead(Right_ENC_A)>0) ? (_LeftEncoderTicks--) : (_LeftEncoderTicks++);
//    _LeftEncoderTicks++;
// }


// Constructor definition outside the class
// void Encoder::init(int right_ENC_CHAN_A, int right_ENC_CHAN_B, int left_ENC_CHAN_A, int left_ENC_CHAN_B) {
//   Right_ENC_CHAN_A = right_ENC_CHAN_A;
//   Right_ENC_CHAN_B = right_ENC_CHAN_B;
//   Left_ENC_CHAN_A = left_ENC_CHAN_A;
//   Left_ENC_CHAN_B = left_ENC_CHAN_B;
//   attachInterrupt(digitalPinToInterrupt(Right_ENC_CHAN_A), SwitchRightEncoder, RISING);
//   attachInterrupt(digitalPinToInterrupt(Right_ENC_CHAN_B), SwitchRightEncoder, RISING);
//   pinMode(Left_ENC_CHAN_A,INPUT_PULLUP);
//   pinMode(Left_ENC_CHAN_B,INPUT_PULLUP);
//   attachInterrupt(digitalPinToInterrupt(Left_ENC_CHAN_A), SwitchLeftEncoder, RISING);
//   attachInterrupt(digitalPinToInterrupt(Left_ENC_CHAN_B), SwitchLeftEncoder, RISING);
// }

// void Encoder::SwitchRightEncoder(){
//    //(digitalSwitch(Right_ENC_A)>0) ? (Right_ENC_CHAN_A_Ticks--) : (Right_ENC_CHAN_A_Ticks++);
//    Right_ENC_CHAN_A_Ticks++;   
//    Right_ENC_CHAN_B_Ticks++;
// }
// void Encoder::SwitchLeftEncoder(){
//    //(digitalSwitch(Right_ENC_A)>0) ? (Left_ENC_CHAN_A_Ticks--) : (Left_ENC_CHAN_A_Ticks++);
//    Left_ENC_CHAN_A_Ticks++;
//    Left_ENC_CHAN_B_Ticks++;
// }

// float Encoder::Read_Right_ENC_CHAN_A(){
//   return Right_ENC_CHAN_A_Ticks; 
  
// }
// float Encoder::Read_Left_ENC_CHAN_B(){
//   return Right_ENC_CHAN_B_Ticks; 
// }

// float Encoder::Read_Left_ENC_CHAN_A(){
//   return Left_ENC_CHAN_A_Ticks; 
// }

// float Encoder::Read_Left_ENC_CHAN_B(){
//   return Left_ENC_CHAN_B_Ticks; 
// }

// void Init_Encoders(int right_ENC_CHAN_A, int right_ENC_CHAN_B, int left_ENC_CHAN_A, int left_ENC_CHAN_B) {
//   Right_ENC_CHAN_A = right_ENC_CHAN_A;
//   Right_ENC_CHAN_B = right_ENC_CHAN_B;
//   Left_ENC_CHAN_A = left_ENC_CHAN_A;
//   Left_ENC_CHAN_B = left_ENC_CHAN_B;

#include "encoder.h"
#include "Arduino.h"

// int Right_ENC_CHAN_A = 0; 
// int Right_ENC_CHAN_B= 2;
// int Left_ENC_CHAN_A = 12;
// int Left_ENC_CHAN_B = 14;

int Right_ENC_CHAN_A = 35; 
int Right_ENC_CHAN_B= 34;
int Left_ENC_CHAN_A = 22;
int Left_ENC_CHAN_B = 23;

double Left_ENC_CHAN_A_Ticks = 0;
double Left_ENC_CHAN_B_Ticks = 0;
double Right_ENC_CHAN_A_Ticks = 0;
double Right_ENC_CHAN_B_Ticks = 0;

void Init_Encoders(){
  pinMode(Left_ENC_CHAN_A,INPUT_PULLUP);
  pinMode(Left_ENC_CHAN_B,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(Right_ENC_CHAN_A), SwitchRightEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(Right_ENC_CHAN_B), SwitchRightEncoder, RISING);

  attachInterrupt(digitalPinToInterrupt(Left_ENC_CHAN_A), SwitchLeftEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(Left_ENC_CHAN_B), SwitchLeftEncoder, RISING);
}

void SwitchRightEncoder(){
   //(digitalSwitch(Right_ENC_A)>0) ? (Right_ENC_CHAN_A_Ticks--) : (Right_ENC_CHAN_A_Ticks++);
   Right_ENC_CHAN_A_Ticks++;   
   Right_ENC_CHAN_B_Ticks++;
}
void SwitchLeftEncoder(){
   //(digitalSwitch(Right_ENC_A)>0) ? (Left_ENC_CHAN_A_Ticks--) : (Left_ENC_CHAN_A_Ticks++);
   Left_ENC_CHAN_A_Ticks++;
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
Serial.println("Right_ENC_CHAN_A : ");
Serial.println(Read_Right_ENC_CHAN_A());
delay (50);
Serial.println("Right_ENC_CHAN_B : ");
Serial.println(Read_Right_ENC_CHAN_B());
delay (50);
Serial.println("Left_ENC_CHAN_A : ");
Serial.println(Read_Left_ENC_CHAN_A());
delay (50);
Serial.println("Left_ENC_CHAN_B : ");
Serial.println(Read_Left_ENC_CHAN_B());
} 