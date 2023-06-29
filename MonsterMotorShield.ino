#include "MMS/MMS.cpp"

MMS mms;

int EN_L = 0;
int EN_R = 0;

// Calculate encoder EN_L
void readLeftEnc(){
  if(digitalRead(EN2A)){
    EN_L++;
  }
 else{
   EN_L--;
  }
}

// Calculate encoder EN_R
void readRightEnc(){
  if(digitalRead(EN2B)){
    EN_R++;
  }
  else{
    EN_R--;
  }
}


void setup(){
  mms.start();
  Serial.begin(9600);
  
  // Interrupt for reading encoders
  attachPCINT(digitalPinToPCINT(EN1A), readLeftEnc, RISING);
  attachPCINT(digitalPinToPCINT(EN1B), readRightEnc, RISING);
}

  void loop() {
    /*mms.set_spd(0.5, 0.0);
    delay(1000);*/
    /*mms.set_spd(100.0, 0.0);
    delay(2500);*/
    /*mms.set_spd(-0.5, 0.0);
    delay(1000);*/
    /*mms.set_spd(-100.0, 0.0);
    delay(2500);*/
    Serial.print(digitalRead(EN1A));
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
    Serial.println();
    delay(1);
}
