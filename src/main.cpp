#include "encoder.h"
#include "motor.h"
#include "Arduino.h"
#include "ultrasound.h"
#include "line_tracker.h"

#include <AceWire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HX711.h"
#include <ArduinoJson.h>
#include <HardwareSerial.h>

// Loadcell
HX711 scale;
#define calibration_factor -800

//OLED display

#define SCREEN_WIDTH 128 // Largeur de l'écran OLED en pixels
#define SCREEN_HEIGHT 64 // Hauteur de l'écran OLED en pixels
#define OLED_RESET -1    // Nécessaire pour les écrans OLED qui ne disposent pas d'un RST dédié
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
HardwareSerial SerialESP(0);

// ultrasound
const int DOUT= 5;
const int CLK= 4;

int default_speed = 70;
int speedA = 70;
int speedB = 70;
bool isBusy = false;
bool dir_changed = false;
bool Office_detected = false;
const int buzzerPin = 17;


// Move regulation

int threshold = 3800;

int pos = 0; // actual position
int dest = 0; // destination

int weight=0;
int moving_sensor[5]={0,0,0,0,0};
int moving_sensor2[5]={0,0,0,0,0};

int n_mem = 9;
int memory[9][5]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
int l_mem[5]={0,0,0,0,0};
int selected_line[5]={0,0,0,0,0};


int ponderation_g[5] = {-3,-1,0,1,3};
int ponderation_d[5] = {3,1,0,-1,-3};
int tab_time[9]={6,5,-3,2,-1,1,-1,1,-1};


void acquisition(){
    moving_sensor[0]=Left2();
    moving_sensor[1]=Left1();
    moving_sensor[2]=Center();
    moving_sensor[3]=Right1();
    moving_sensor[4]=Right2();
    moving_sensor2[0]=moving_sensor[0];
    moving_sensor2[1]=moving_sensor[1];
    moving_sensor2[2]=moving_sensor[2];
    moving_sensor2[3]=moving_sensor[3];
    moving_sensor2[4]=moving_sensor[4];
}

void keep_memory(){
    for (int i=0; i<(n_mem); i++){
        for (int j=0; j<5;j++){
            memory[n_mem-i][j] = memory[n_mem-1-i][j];
        }
    }
    for (int i=0;i<5;i++){
        if(moving_sensor[i]<threshold){
            memory[0][i] = 1;
        }
        else{
            memory[0][i] = 0;
        }
    }
}

void clean_mem(){
    for(int i=0;i<n_mem;i++){
        for(int j=0;j<5;j++){
            memory[i][j]=0;
        }
    }
}



String getBotstate() {
  String botstate[4] = {"idle", "busy", "error","off"};
  if (!isBusy) {
    return botstate[0];
  }
  else {
    return botstate[1];
  }
}

void sendData(){
  DynamicJsonDocument state(1024);
  state["botstate"] = getBotstate();
  state["batterystate"] = 85;
  state["location"] = pos;
  state["weight"] = weight;
  String jsonString;
  serializeJson(state, jsonString);
  Serial.println(jsonString);
}

void listenDest(){
  if (Serial.available()>0){
    dest = Serial.parseInt();// Lire les données entrantes et les convertir en valeur numérique,si serial.read() on aura le numero mais en ascii
  }
}



void displayAll(){ 
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Weight: ");
    display.print(weight);
    display.print(" g");
    display.setCursor(0,20);
    display.print("Pos: ");
    display.print(pos);
    display.setCursor(0,40);
    display.print("Dest: ");
    display.print(dest);
    display.display();
}

void check_office(){
    if(memory[0][1]==1 && memory[0][2]==1 && memory[0][3]==1 && (memory[0][4]==1||memory[0][0]==1)){
        // Serial.print("Nouveau bureau Office_detectede \n");
        if(pos<dest){
            pos+=1;
        }
        else if(dest<pos){
            pos-=1;
        }
        Office_detected = true;
        displayAll();
        sendData();
    }
}

void select_line(int tab[9][5], int n){
    for(int i=0;i<5;i++){
        selected_line[i]=tab[n][i];
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

void Compute_regulation(int tab[9][5]){
    // make a copy of memory array on a new array
    int tab0[5]={0,0,0,0,0};
    select_line(tab,0);
    for(int i=0;i<5;i++){
        tab0[i]=selected_line[i];
    }

    select_line(tab,1);
    int tab1[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab1[i]=selected_line[i];
    }

    select_line(tab,2);
    int tab2[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab2[i]=selected_line[i];
    }

    select_line(tab,3);
    int tab3[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab3[i]=selected_line[i];
    }
    select_line(tab,4);
    int tab4[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab4[i]=selected_line[i];
    }
    select_line(tab,5);
    int tab5[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab5[i]=selected_line[i];
    }
    select_line(tab,6);
    int tab6[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab6[i]=selected_line[i];
    }
    select_line(tab,7);
    int tab7[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab7[i]=selected_line[i];
    }
    select_line(tab,8);
    int tab8[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        tab8[i]=selected_line[i];
    }
    // Compute regulated speed of each wheel
    speedA = default_speed+tab_time[0]*cal_g(tab0)+tab_time[1]*cal_g(tab1)+tab_time[2]*cal_g(tab2)+tab_time[3]*cal_g(tab3)+tab_time[4]*cal_g(tab4)+tab_time[5]*cal_g(tab5)+tab_time[6]*cal_g(tab6)+tab_time[7]*cal_g(tab7)+tab_time[8]*cal_g(tab8);
    speedB = default_speed+tab_time[0]*cal_d(tab0)+tab_time[1]*cal_d(tab1)+tab_time[2]*cal_d(tab2)+tab_time[3]*cal_d(tab3)+tab_time[4]*cal_d(tab4)+tab_time[5]*cal_d(tab5)+tab_time[6]*cal_d(tab6)+tab_time[7]*cal_d(tab7)+tab_time[8]*cal_d(tab8);
   
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
    move_backward(default_speed,default_speed);
    double ticks_for_turn = 475;
    double  previous_ticks = Read_Left_ENC_CHAN_A();
    double  actual_ticks = Read_Left_ENC_CHAN_A();
    double ticks = 0;

    while (ticks < ticks_for_turn){
    actual_ticks = Read_Left_ENC_CHAN_A();
    ticks = actual_ticks - previous_ticks;
    }
    stop_motors();
    clean_mem();
    dir_changed=!dir_changed;
}


void move_regulation(){
    if ( moving_sensor[0]>threshold && moving_sensor[1]>threshold && moving_sensor[2]>threshold && moving_sensor[3]>threshold && moving_sensor[4]>threshold){
        stop_motors();
        clean_mem();
    }
    else if (moving_sensor[0]<threshold && moving_sensor[1]>threshold && moving_sensor[2]>threshold && moving_sensor[3]>threshold && moving_sensor[4]<threshold){
        stop_motors();
        clean_mem();
    }
    else if (memory[0][0]==1 || memory[0][1]==1 || memory[0][2]==1 || memory[0][3]==1 || memory[0][4]==1){
        move_forward(speedA,speedB);
    }
    else{
        stop_motors();
        clean_mem();
    }
}

void set_dest(int n_bureau){
    if(!isBusy){
        dest=n_bureau;
        isBusy=true;
        delay(2000);
    }
}

void move(){
    isBusy=true;
    clean_mem();
    while((pos!=dest)){
        if (((dest<pos)&&(!dir_changed))||((dest>pos)&&(dir_changed))){
            change_direction();
            clean_mem();
        }
        switch_ultrasounds();
        if((read_ultrasound1()<30)||(read_ultrasound2()<30)){
            stop_motors();
            clean_mem();
        }
        else{
        acquisition();
        keep_memory();
        if (!Office_detected){
            check_office();
        }
        else if(memory[0][0]==1 && memory[0][4]==1){
            Office_detected=false;
        }
        Compute_regulation(memory);      
        move_regulation();
        }
    }
    if (pos==dest){
        stop_motors();
        clean_mem();
        isBusy=false;
    }
}

void weigh(){
    weight = scale.get_units(10);
    // affWeight = weight/1000; // conversion to kg
}

void overload_alert(){
    tone(buzzerPin, 550);
    weigh();
    sendData();
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(3);
    display.print("Warning !");
    display.setCursor(0,30);
    display.setTextSize(2);
    display.print("Overload :");
    display.display();
    dest=pos;
}

void setup() {
    Serial.begin(115200);
    pinMode(buzzerPin, OUTPUT);
    Init_Encoders();
    init_motors();
    init_untrasounds();   
    init_tracker();
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.display();
    scale.begin(DOUT, CLK);
    scale.set_scale(450.0f);
    scale.tare();
    displayAll();
}

void loop() {
   while((pos==dest)){
        stop_motors();
        sendData();
        listenDest();
        weigh();
        displayAll();
    }
    if(weight<1000){
    move();
    }
    else
    { 
     while (weight>1000) {
        overload_alert();}        
 }
tone(buzzerPin, 0);
}