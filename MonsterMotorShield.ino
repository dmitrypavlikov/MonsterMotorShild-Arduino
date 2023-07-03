#include "MMS/MMS.cpp"

MMS mms;

// Encoder variables
int64_t PRESENT_EN_L = 0;
int64_t PRESENT_EN_R = 0;
int64_t PAST_EN_L = 0;
int64_t PAST_EN_R = 0;

float PRESENT_VEL_L = 0;
float PRESENT_VEL_R = 0;
float PAST_VEL_L = 0;
float PAST_VEL_R = 0;

float PID_L = 0;
float PID_R = 0;
float I_PID_L = 0;
float I_PID_R = 0;
float P_L = 12;
float I_L = 0; //2
float D_L = 0;  //0
float P_R = 12; 
float I_R = 0; //1.7
float D_R = 0;  //0


// Временная переменная, в которую нам задали линейную скорость каждого колеса
float lin = 5; // mm/s

// Миллис
unsigned long timer;

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

float calculate_PID(float image_vel, float real_vel, float freq){
  /*I_PID_L += (image_vel - real_vel) * (freq / 1000) * I;
  PID = (image_vel - real_vel) * P + I_PID; */
  return 0;
  
}

void calculate_vel(int freq){
 PRESENT_VEL_L = ((PRESENT_EN_L - PAST_EN_L) * WHEEL_DIAMETER * 3.14) / (TIX_PER_SPIN_L * freq); // mm/s
 PRESENT_VEL_R = ((PRESENT_EN_R - PAST_EN_R) * WHEEL_DIAMETER * 3.14) / (TIX_PER_SPIN_R * freq); // mm/s
 
 // TODO angular vel

 //mms.set_pwm(calculate_PID(lin, PRESENT_VEL_L, freq), calculate_PID(lin, PRESENT_VEL_R, freq));
 
 if ((PID_L > -10)&&(PID_L < 10)){I_PID_L = 0;}
 if ((PID_R > -10)&&(PID_R < 10)){I_PID_R = 0;}
 
 //if (PRESENT_VEL_L < 0) {P_L = 11;} else {P_L = 10;}
 //if (PRESENT_VEL_R < 0) {P_R = 11;} else {P_R = 10;}
 
 
 
 I_PID_L += (lin - PRESENT_VEL_L) * freq / 1000 * I_L;
 I_PID_R += (lin - PRESENT_VEL_R) * freq / 1000 * I_R;
 PID_L = (lin - PRESENT_VEL_L) * P_L + I_PID_L;
 PID_R = (lin - PRESENT_VEL_R) * P_R + I_PID_R;
 PID_L += (PRESENT_VEL_L - PAST_VEL_L) * D_L;
 PID_R += (PRESENT_VEL_R - PAST_VEL_R) * D_R;
 mms.set_pwm(PID_L, PID_R);
 
 
 //PID = (lin - PRESENT_VEL_L) * P;

 PAST_VEL_L = PRESENT_VEL_L;
 PAST_VEL_R = PRESENT_VEL_R;
 PAST_EN_L = PRESENT_EN_L;
 PAST_EN_R = PRESENT_EN_R;

}

void setup(){
  mms.start();
  Serial.begin(9600);
  
  // Interrupt for reading encoders
  attachPCINT(digitalPinToPCINT(EN1A), readLeftEnc, RISING);
  attachPCINT(digitalPinToPCINT(EN1B), readRightEnc, RISING);


  // Миллис
  timer = millis();
  }

  void loop() {
    
    calculate_vel(50);
    Serial.print(PRESENT_VEL_L);
    Serial.print("  ");
    Serial.print(PRESENT_VEL_R);
    Serial.print("  |  ");
    Serial.print(int(PRESENT_EN_L));
    Serial.print("  ");
    Serial.print(int(PRESENT_EN_R));
    Serial.print("  |  ");
    Serial.print(PID_L);
    Serial.print("  ");
    Serial.println(PID_R);

    if(millis() - timer >= 5000){
      if(lin > 0){ lin++;}
      lin = -lin;
      timer = millis();
    }
    /*mms.set_spd(0.5, 0.0);
    delay(1000);*/
    /*mms.set_spd(100.0, 0.0);
    delay(2500);*/
    /*mms.set_spd(-0.5, 0.0);
    delay(1000);*/
    /*mms.set_spd(-100.0, 0.0);
    delay(2500);*/
    /*Serial.print(digitalRead(EN1A));
    Serial.print("  ");
    Serial.print(digitalRead(EN2A));
    Serial.print("  ");
    Serial.print(EN_L);
    Serial.print("  |  ");
    Serial.print(digitalRead(EN1B));
    Serial.print("  ");
    Serial.print(digitalRead(EN2B));
    Serial.print("  ");
    Serial.print(EN_R);
    Serial.println();*/
    
    delay(50);
}
