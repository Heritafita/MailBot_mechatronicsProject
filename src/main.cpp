#include <stdbool.h>
#include "encoder.h"
#include "motor.h"
#include "Arduino.h"
#include "ultrasound.h"
#include "line_tracker.h"

bool isBusy = false;
bool Detect_Office = false;


int speedA = 50;
int speedB = 50;

// int move = 60;


int threshold = 4000;

bool get_isBusy(){
    return isBusy;}

 

void Send(int dest, int start_pos){
	// #def vars
	int old_dest = dest;
	int actual_pos = start_pos;
	// int cooldown = 0;  //cooldown pour éviter de voir plusieurs fois le même bureau
	isBusy = true;  //var global
	// #main
	if (dest < start_pos){
		change_direction();}
	while (actual_pos != old_dest)
	{
		move_regulation();
		// if (Detect_Office && (cooldown == 0)){
		if (Detect_Office) {
			if (dest > start_pos){
				actual_pos += 1;}
			else {
				actual_pos -= 1;
			}
			// cooldown = 50; // arbitraire
            Detect_Office = false;
			}
		// if (cooldown != 0) {
		// 	cooldown -=1;	}
		// 	}
	isBusy = false;}
}

void turn_left(){
move_forward(0, speedB);
 double ticks_for_turn = 400;
   double  previous_ticks = Read_Right_ENC_CHAN_A();
   double  actual_ticks = Read_Right_ENC_CHAN_A();
   double ticks = 0;
   
   while (ticks < ticks_for_turn)
   {
    actual_ticks = Read_Right_ENC_CHAN_A();
    ticks = actual_ticks - previous_ticks;
    }
    stop_motors();
}

void turn_right(){
move_forward(speedA, 0);
 double ticks_for_turn = 400;
   double  previous_ticks = Read_Left_ENC_CHAN_A();
   double  actual_ticks = Read_Left_ENC_CHAN_A();
   double ticks = 0;
   
   while (ticks < ticks_for_turn)
   {
    actual_ticks = Read_Left_ENC_CHAN_A();
    ticks = actual_ticks - previous_ticks;
    }
stop_motors();
}


void change_direction(){
move_forward(speedA, 0);
    double ticks_for_turn = 1600;
   double  previous_ticks = Read_Left_ENC_CHAN_A();
   double  actual_ticks = Read_Left_ENC_CHAN_A();
   double ticks = 0;
   
   while (ticks < ticks_for_turn)
   {
    actual_ticks = Read_Left_ENC_CHAN_A();
    ticks = actual_ticks - previous_ticks;
    }
stop_motors();
}

void move_regulation(){
    if (Left2()>threshold && Left1()>threshold && Center()>threshold && Right1()>threshold && Right2()>threshold){
        stop_motors();
    }
    else if ( Left2()>threshold && Left1()>threshold && Center()<threshold && Right1()>threshold && Right2()>threshold){
        move_forward(speedA, speedB);
    }   
    else if ( Left2()>threshold && Left1()<threshold && Center()>threshold && Right1()>threshold && Right2()>threshold){
        move_right(speedA, speedB);
    }
     else if ( Left2()>threshold && Left1()<threshold  && Center()<threshold  && Right1()>threshold && Right2()>threshold){
        move_right(speedA, speedB);
    }
     else if ( Left2()>threshold && Left1()>threshold && Center()>threshold && Right1()<threshold && Right2()>threshold){
        move_left(speedA, speedB);
    }
    else if ( Left2()>threshold && Left1()>threshold && Center()<threshold && Right1()<threshold && Right2()>threshold){
        move_left(speedA, speedB);
    }
    //move left
    else if ( Left2()<threshold && Left1()<threshold && Center()<threshold && Right1()>threshold && Right2()>threshold){
        turn_left();
    }
    //move right
    else if ( Left2()>threshold && Left1()>threshold && Center()<threshold && Right1()<threshold && Right2()<threshold){
        turn_right();
    }
    //  // stop
     else if ( Left2()<threshold && Left1()<threshold && Center()<threshold && Right1()<threshold && Right2()<threshold){
        Detect_Office = true;
    else 
    {
       stop_motors(); 
    }
    // }
}

void setup() {
delay (500);
Serial.begin(115200);
Init_Encoders();
init_motors();
init_untrasounds();  
// move_forward(speedA, speedB);  
init_tracker();

}

void loop() {
    // turn_left();
    
    // delay(2000);
    // turn_right();

// display_tracker();
// move_left(speedA, speedB);

// move_left(speedA, speedB);

switch_ultrasounds();
if((read_ultrasound1()<30)||(read_ultrasound2()<30)){
    stop_motors();
   }
   else{
    move_regulation(); 
    // Send(3, 1);
   }
// // move_regulation();
// display_distances();
// display_encoders();
// delay(200);
// }
}