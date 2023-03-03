// class Encoder {        // The class
//   public:          // Access specifier
//     int Right_ENC_CHAN_A;  // Attribute
//     int Right_ENC_CHAN_B;
//     int Left_ENC_CHAN_A;
//     int Left_ENC_CHAN_B;
//     float Left_ENC_CHAN_A_Ticks = 0;
//     float Left_ENC_CHAN_B_Ticks = 0;
//     float Right_ENC_CHAN_A_Ticks = 0;
//     float Right_ENC_CHAN_B_Ticks = 0;
//     void init(string x, string y, int z); // Constructor declaration
//     void SwitchRightEncoder();
//     void SwitchLeftEncoder();
//     float Read_Right_ENC_CHAN_A();
//     float Read_Left_ENC_CHAN_B();
//     float Read_Left_ENC_CHAN_A();
//     float Read_Left_ENC_CHAN_B();
// };

// #define Right_ENC_CHAN_A 12
// #define Right_ENC_CHAN_B 13
// #define Left_ENC_CHAN_A 14
// #define Left_ENC_CHAN_B  32


// void Init_Encoders(int right_ENC_CHAN_A, int right_ENC_CHAN_B, int left_ENC_CHAN_A, int left_ENC_CHAN_B);
void Init_Encoders();
void SwitchRightEncoder();
void SwitchLeftEncoder();
double Read_Right_ENC_CHAN_A();
double Read_Right_ENC_CHAN_B();
double Read_Left_ENC_CHAN_A();
double Read_Left_ENC_CHAN_B();


