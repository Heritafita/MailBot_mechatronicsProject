#include "encoder.h"
#include "motor.h"
#include "Arduino.h"
#include "ultrasound.h"
#include "line_tracker.h"

int def_speed = 90;
int speedA = 90;
int speedB = 90;
bool isBusy = false;
bool dir_changed = false;


// int move = 60;

int threshold = 3800;

bool fwd = true;

int pos = 2;
int dest = 0;
int tmp_pos = 2;
int cd = 0;
int capteurs[5]={0,0,0,0,0};
int capteurs2[5]={0,0,0,0,0};

int n_mem = 9;
int memory[9][5]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
int l_mem[5]={0,0,0,0,0};
int ligne_choisie[5]={0,0,0,0,0};


int ponderation_g[5] = {-3,-1,0,1,3};
int ponderation_d[5] = {3,1,0,-1,-3};
int tab_time[9]={5,4,3,-2,1,-1,1,-1};

void acquisition(){
    capteurs[0]=Left2();
    capteurs[1]=Left1();
    capteurs[2]=Center();
    capteurs[3]=Right1();
    capteurs[4]=Right2();
    capteurs2[0]=capteurs[0];
    capteurs2[1]=capteurs[1];
    capteurs2[2]=capteurs[2];
    capteurs2[3]=capteurs[3];
    capteurs2[4]=capteurs[4];
}

void keep_memory(){
    for (int i=0; i<(n_mem); i++){
        for (int j=0; j<5;j++){
            memory[n_mem-i][j] = memory[n_mem-1-i][j];
        }
    }
    for (int i=0;i<5;i++){
        if(capteurs[i]<threshold){
            memory[0][i] = 1;
        }
        else{
            memory[0][i] = 0;
        }
    }
}

void check_bureau(){
    if( capteurs[0]<threshold && capteurs[1]<threshold && capteurs[2]<threshold && capteurs[3]<threshold && capteurs[4]<threshold){
        if(pos<dest){
            pos+=1;
        }
        cd = 15;
    }
}

void chose_line(int tab[9][5], int n){
    for(int i=0;i<5;i++){
        ligne_choisie[i]=tab[n][i];
    }
}

int cal_d(int tab[5]){
    int res = 0;
    for(int i=0;i<5;i++){
        res+=tab[i]*ponderation_d[i];
    }
    return res;
}

int cal_g(int tab[5]){
    int res = 0;
    for(int i=0;i<5;i++){
        res+=tab[i]*ponderation_g[i];
    }
    return res;
}

void calcul_reg(int tab[9][5]){
    // On prend chaque ligne 1 à 1...
    int tab0[5]={0,0,0,0,0};
    chose_line(tab,0);
    for(int i=0;i<5;i++){
        tab0[i]=ligne_choisie[i];
    }

    chose_line(tab,1);
    int tab1[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab1[i]=ligne_choisie[i];
    }

    chose_line(tab,2);
    int tab2[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab2[i]=ligne_choisie[i];
    }

    chose_line(tab,3);
    int tab3[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab3[i]=ligne_choisie[i];
    }
    chose_line(tab,4);
    int tab4[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab4[i]=ligne_choisie[i];
    }
    chose_line(tab,5);
    int tab5[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab5[i]=ligne_choisie[i];
    }
    chose_line(tab,6);
    int tab6[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab6[i]=ligne_choisie[i];
    }
    chose_line(tab,7);
    int tab7[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab7[i]=ligne_choisie[i];
    }
    // ... Puis on calcule la vitesse régulée
    speedA = def_speed+tab_time[0]*cal_g(tab0)+tab_time[1]*cal_g(tab1)+tab_time[2]*cal_g(tab2)+tab_time[3]*cal_g(tab3)+tab_time[4]*cal_g(tab4)+tab_time[5]*cal_g(tab5)+tab_time[6]*cal_g(tab6)+tab_time[7]*cal_g(tab7);
    speedB = def_speed+tab_time[0]*cal_d(tab0)+tab_time[1]*cal_d(tab1)+tab_time[2]*cal_d(tab2)+tab_time[3]*cal_d(tab3)+tab_time[4]*cal_d(tab4)+tab_time[5]*cal_d(tab5)+tab_time[6]*cal_d(tab6)+tab_time[7]*cal_d(tab7);
}


void turn_left(){
    move_forward(0, speedB);
    double ticks_for_turn = 300;
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
    double previous_ticks = Read_Left_ENC_CHAN_A();
    double actual_ticks = Read_Left_ENC_CHAN_A();
    double ticks = 0;
    
    while (ticks < ticks_for_turn)
    {
        actual_ticks = Read_Left_ENC_CHAN_A();
        ticks = actual_ticks - previous_ticks;
        }
    stop_motors();
}

void change_direction(){
    move_backward(speedA,speedA);
    double ticks_for_turn = 550;
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
    if ( capteurs[0]>threshold && capteurs[1]>threshold && capteurs[2]>threshold && capteurs[3]>threshold && capteurs[4]>threshold){
        stop_motors();
    }
    else if (capteurs[0]<threshold && capteurs[1]>threshold && capteurs[2]>threshold && capteurs[3]>threshold && capteurs[4]<threshold){
        stop_motors();
    }
    // On a atteint la destination
    /*else if( capteurs[0]<threshold && capteurs[1]<threshold && capteurs[2]<threshold && capteurs[3]<threshold && capteurs[4]<threshold && pos == dest){
        stop_motors();
        send_notif();
    }
    //move left
    else if ( capteurs[0]<threshold && capteurs[1]<threshold && capteurs[2]<threshold && capteurs[3]>threshold && capteurs[4]>threshold){
        turn_left();
    }
    //move right
    else if ( capteurs[0]>threshold && capteurs[1]>threshold && capteurs[2]<threshold && capteurs[3]<threshold && capteurs[4]<threshold){
        turn_right();
    }*/
    else if (memory[0][0]==1 || memory[0][1]==1 || memory[0][2]==1 || memory[0][3]==1 || memory[0][4]==1){
        move_forward(speedA,speedB);
    }
    else{
        stop_motors();
    }
}

void setup() {
delay (1500);
Serial.begin(115200);
Init_Encoders();
init_motors();
init_untrasounds();  
// move_forward(speedA, speedB);  
init_tracker();
}

void loop() {
    switch_ultrasounds();
    if((read_ultrasound1()<30)||(read_ultrasound2()<30)){
        stop_motors();
    }
    else if (pos!=dest){
        if ((dest<pos)&&(!dir_changed)){
            change_direction();
            tmp_pos=pos;
            pos=dest;
            dest=tmp_pos;
            dir_changed=true;
        }
        acquisition();
        keep_memory();
        if (cd == 0){
            check_bureau();
        }
        else{
            cd-=1;
        }
        calcul_reg(memory);
        Serial.println(speedA); 
        Serial.println(speedB);    
        Serial.print("new \n");
        move_regulation();
    }
    else{
        stop_motors();
    }

    // turn_left();

    // delay(2000);
    // turn_right();

// display_tracker();
// move_left(speedA, speedB);

// move_left(speedA, speedB);

// switch_ultrasounds();
// if((read_ultrasound1()<30)||(read_ultrasound2()<30)){
//     stop_motors();
//    }
//    else{
//     // move_regulation();
//     move_forward(speedA, speedB);  
    
//    }

// display_distances();
// display_encoders();
// delay(200);
}