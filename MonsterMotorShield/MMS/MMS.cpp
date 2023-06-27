/*      MPNSTER MOTOR SHIELD        */
#include "Arduino.h"

// Left motor
#define DIR1A   2   // Direction CW
#define DIR2A   3   // Direction CWW 1B
#define PWM1    4   // Speed (0-255)
#define TRQ1    A0  // #IF PINMODE=OUTPUT# Torque (HIGH=Enable)
#define DIAG1   A0  // #IF PINMODE=INPUT#  Diagnostic (HIGH=NO_PROBLEM)
#define CUR1    A2  // Present Current (0-1023) (0-65 mA)

// Right motor
#define DIR1B   5   // Direction CW 1B
#define DIR2B   6   // Direction CWW 
#define PWM2    7   // Speed (0-255)
#define TRQ2    A1  // #IF PINMODE=OUTPUT# Torque (HIGH=Enable)
#define DIAG2    A1  // ##IF PINMODE=INPUT#  Diagnostic (HIGH=NO_PROBLEM)
#define CUR2    A3  // Present Current (0-1023) (0-65 mA)

// Encoder settings
/*#define EN1A    //TODO
#define EN1B    //TODO
#define EN2A    //TODO
#define EN2B    //TODO
#define */

// Robot settings
#define BASE_WIDTH 0.315
#define MAX_CURRENT 10  //TODO or not use
#define MAX_VEL 3.5


class MMS 
{
  public:
  int CURRENT_L = 0;
  int CURRENT_R = 0;

  // All pinMode in one function
  void start(){
    // Left motor
    pinMode(PWM1,OUTPUT);
    pinMode(DIR1A,OUTPUT);
    pinMode(DIR2A,OUTPUT);
    pinMode(DIAG1,INPUT);    // ATTENTION: Torque pin in Diagnostic workmode
    pinMode(CUR1,INPUT);
  
    // Right motor
    pinMode(PWM2,OUTPUT);
    pinMode(DIR1B,OUTPUT);
    pinMode(DIR2B,OUTPUT);
    pinMode(DIAG2,INPUT);   // ATTENTION: Torque pin in Diagnostic workmode
    pinMode(CUR2,INPUT);
 
    /*Encoders*/
    /*pinMode(EN1A, INPUT_PULLUP);
    pinMode(EN1B, INPUT_PULLUP);
    pinMode(EN2A, INPUT_PULLUP);
    pinMode(EN2B, INPUT_PULLUP);*/

    }
  
  void clear(){
    SPD_L = 0;
    SPD_R = 0;
  }
  
  // Make wheels free for spinning by hands, zero speed
  void torque_disable(){
    analogWrite(PWM1, 0);  
    analogWrite(PWM2, 0);
    digitalWrite(DIR1A,LOW); digitalWrite(DIR2A,LOW);
    digitalWrite(DIR1B,LOW); digitalWrite(DIR2B,LOW);
  }
  
  // Emergency STOP of motors by torque disable and zero spd
  // void brake_motors(){;}
 
  // Set speed of motors by linear and angular velocity
  void set_spd(float linear, float angular){
    clear();
    
    // Calculate velocity to speed of each wheel
    SPD_L = round(linear - angular * BASE_WIDTH / 2.0) * 75;
    SPD_R = round(linear + angular * BASE_WIDTH / 2.0) * 75;

    // Set the spinning direction of each wheel
    if(linear - angular * BASE_WIDTH / 2.0 > 0.0) {
      digitalWrite(DIR1A,HIGH); digitalWrite(DIR2A,LOW);
    }
    if(linear - angular * BASE_WIDTH / 2.0 < 0.0) {
     digitalWrite(DIR1A,LOW); digitalWrite(DIR2A,HIGH);
    }
    if(linear + angular * BASE_WIDTH / 2.0 > 0.0) {
     digitalWrite(DIR1B,HIGH); digitalWrite(DIR2B,LOW);
    }
    if(linear + angular * BASE_WIDTH / 2.0 < 0.0) {
      digitalWrite(DIR1B,LOW); digitalWrite(DIR2B,HIGH);
    }

    

    Serial.print(linear - angular * BASE_WIDTH / 2.0);
    Serial.print("  ");
    Serial.print(linear + angular * BASE_WIDTH / 2.0);
    Serial.print(" | ");
    Serial.print(SPD_L);
    Serial.print("  ");
    Serial.println(SPD_R);

    analogWrite(PWM1, abs(SPD_L));  
    analogWrite(PWM2, abs(SPD_R));
    }

  private:
  int16_t SPD_L = 0;
  int16_t SPD_R = 0;
  
  float PID = 0;
  float P = 0;
  float I = 0;
  float D = 0;

  

  


  

  
};