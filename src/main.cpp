#include "encoder.h"
#include "motor.h"
#include "Arduino.h"
#include "ultrasound.h"

int speedA = 75;
int speedB = 75;


void setup() {
Serial.begin(115200);
Init_Encoders();
init_motors();
init_untrasounds();  
// move_forward(speedA, speedB);  
}

void loop() {

switch_ultrasounds();
if((read_ultrasound1()<30)||(read_ultrasound2()<30)){
    stop_motors();
   }
   else{
    move_forward(speedA, speedB); 
   }

display_distances();
display_encoders();
}


