#include "encoder.h"
#include "motor.h"
#include "Arduino.h"
#include "ultrasound.h"

int speedA = 75;
int speedB = 75;


void setup() {
Serial.begin(115200);
Init_Encoders();
// init_motors();
// init_untrasounds();  
// move_forward(speedA, speedB);  
}

void loop() {
// switch_ultrasounds();
// if (read_ultrasound1()<=30) {
//     stop_motors();
    
// }
// else{
// move_forward(speedA,speedB);
// Serial.println("Distance 1 : ");
// Serial.println(read_ultrasound1());
// Serial.println("OK Capt ");
// Serial.flush();
// Serial.println("Distance 2 : ");
// Serial.println(read_ultrasound2());
// if ((read_ultrasound1()<=30) || (read_ultrasound2()<=30)) {
//     stop_motors();
// }


Serial.println("Right_ENC_CHAN_A : ");
Serial.println(Read_Right_ENC_CHAN_A());
delay (100);

Serial.println("Right_ENC_CHAN_B : ");
Serial.println(Read_Right_ENC_CHAN_B());
delay (100);

Serial.println("Left_ENC_CHAN_A : ");
Serial.println(Read_Left_ENC_CHAN_A());
delay (100);

Serial.println("Left_ENC_CHAN_B : ");
Serial.println(Read_Left_ENC_CHAN_B());
}


