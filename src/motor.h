// Motor A, Left 
// #define enA  15
// #define in1  26
// #define in2  22

// // Motor B, Right
 
// #define enB  32
// #define in3  23
// #define in4  21

void init_motors();
void move_forward(int pwmA, int pwmB);
void stop_motors();
void move_left(int pwmA, int pwmB);
void move_right(int pwmA, int pwmB);
