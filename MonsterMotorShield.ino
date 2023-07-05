#include "MMS/MMS.cpp"

/***********SERIAL DEFINES***********/
// IF cmd_vel not recived during 2 sec => vel = 0
#define CMD_VEL_TIMEOUT 3000

// Baudrate for serial communication
#define SERIAL_BAUD 115200

// Rate for serial timeout [ms]
#define SERIAL_RATE 10 
/*******END OF SERIAL DEFINES*******/


MMS mms;

// Encoder variables
int64_t PRESENT_EN_L = 0;
int64_t PRESENT_EN_R = 0;
int64_t PAST_EN_L = 0;
int64_t PAST_EN_R = 0;

// Velocity variables
float PRESENT_VEL_L = 0;
float PRESENT_VEL_R = 0;
float PAST_VEL_L = 0;
float PAST_VEL_R = 0;

// Linear vel and angular vel variables
float lin = 0.0; // m/s
float ang = 0.0; // m/s  (+ CWW | - CW)

// Left motor PID variables
float PID_L = 0;        // Error
float I_PID_L = 0;      // Integral Error
float P_L = 350;        // P coefficient
float I_L = 60;         // I coefficient
float D_L = 0;          // D coefficient

// Right motor PID variables
float PID_R = 0;        // Error  
float I_PID_R = 0;      // Integral Error
float P_R = 350;        // P coefficient
float I_R = 60;         // I coefficient
float D_R = 0;          // D coefficient


// Millis timer
unsigned long timer;



void setup(){
  delay(1000);
  Serial.begin(SERIAL_BAUD);
  Serial.setTimeout(SERIAL_RATE);
  
  
  
  
  mms.start();
  
  // Interrupt for reading encoders
  attachPCINT(digitalPinToPCINT(EN1A), readLeftEnc, RISING);
  attachPCINT(digitalPinToPCINT(EN1B), readRightEnc, RISING);

  // Initialize global timer
  timer = millis();
  }


void loop() {
        
    calculate_vel(lin, ang, 0.05);
    
  // Check velocity timeout
  if(millis() - timer >= CMD_VEL_TIMEOUT){
    lin = 0.0;
    ang = 0.0;
    mms.motor_stop();
  }
    delay(50);
}


// Reading encoder PRESENT_EN_L
void readLeftEnc(){
  if(digitalRead(EN2A)){
    PRESENT_EN_L++;
  }
  else{
   PRESENT_EN_L--;
  }
}

// Reading encoder PRESENT_EN_R
void readRightEnc(){
  if(digitalRead(EN2B)){
    PRESENT_EN_R++;
  }
  else{
    PRESENT_EN_R--;
  }
}

// Recive linear vel, angular vel, frequency of work cycle
// Calculate encoders speed to velocity of each wheels
// Check difference between recived vel and encoders vel
// Tune vel of each wheel with PID, convert answers to PWM
// Send PWM to Monster Motor Shield 
void calculate_vel(float lin, float ang, float freq){

  // Calculate encoders speed to velocity of each wheels
  PRESENT_VEL_L = ((PRESENT_EN_L - PAST_EN_L) * WHEEL_DIAMETER * 3.14) / (TIX_PER_SPIN_L * freq); // m/s
  PRESENT_VEL_R = ((PRESENT_EN_R - PAST_EN_R) * WHEEL_DIAMETER * 3.14) / (TIX_PER_SPIN_R * freq); // m/s

  // NOT USED YET
  //if ((PID_L > -10)&&(PID_L < 10)){I_PID_L = 0;}
  //if ((PID_R > -10)&&(PID_R < 10)){I_PID_R = 0;}
  // NOT USED YET
  //if (PRESENT_VEL_L < 0) {P_L = 11;} else {P_L = 10;}
  //if (PRESENT_VEL_R < 0) {P_R = 11;} else {P_R = 10;}

  // Calculate and encrease Integral part of PID
  I_PID_L += (lin - (ang*BASE_WIDTH) - PRESENT_VEL_L) * freq * I_L;
  I_PID_R += (lin + (ang*BASE_WIDTH) - PRESENT_VEL_R) * freq * I_R;

  // Calculate PID
  PID_L = (lin -(ang*BASE_WIDTH) - PRESENT_VEL_L) * P_L + I_PID_L;
  PID_R = (lin + (ang*BASE_WIDTH)- PRESENT_VEL_R) * P_R + I_PID_R;
  PID_L += (PRESENT_VEL_L - PAST_VEL_L) * D_L;
  PID_R += (PRESENT_VEL_R - PAST_VEL_R) * D_R;

  // Send PWM to Moster Motor Shield
  mms.set_pwm(PID_L, PID_R);

  // Update previous data
  PAST_VEL_L = PRESENT_VEL_L;
  PAST_VEL_R = PRESENT_VEL_R;
  PAST_EN_L = PRESENT_EN_L;
  PAST_EN_R = PRESENT_EN_R;
}

/**********SERIAL FUNCTIONS SPACE***********/
// Reading and decoding cmd_vel from Serial port
void serialEvent(){
  if(Serial.available()){
    // Buffer for reciving mail from Serial
    char mail[12]={}; // [+x.xx,+x.xx/n] 12 chars
    // Reading mail to buffer
    Serial.readBytesUntil('\n', mail, 12);

    // Local buffer for parts of mail
    String num;
    // Variable for splitting mail on 2 parts
    bool split = true;

    // Mail splitting cycle
    for(int i=0; i<sizeof(mail); i++){
      if(mail[i] != ','){
        num += mail[i];
      }else{
        // Read linear velocity
        lin = num.toFloat();
        num = "";
        }
    }
    // Read angular velocity
    ang = num.toFloat();
    timer = millis();
  }
}

//void send
