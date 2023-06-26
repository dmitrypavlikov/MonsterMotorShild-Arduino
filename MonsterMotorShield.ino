
// Left motor
#define DIR1A   2   //Direction CW
#define DIR2A   3   //Direction CWW 1B
#define PWM1    4   //Speed (0-255)
#define TRQ1    A0  //Torque (HIGH=Enable)
#define CUR1    A2  //Present Current (0-1023)

// Right motor
#define DIR1B   5   //Direction CW 1B
#define DIR2B   6   //Direction CWW 
#define PWM2    7   //Speed (0-255)
#define TRQ2    A1  //Torque (HIGH=Enable)
#define CUR2    A3  //Present Current (0-1023)

// Encoder settings
/*#define EN1A    //TODO
#define EN1B    //TODO
#define EN2A    //TODO
#define EN2B    //TODO
#define */

// Robot settings
#define BASE_WIDTH 0.315
#define MAX_CURRENT 10  //TODO 
#define MAX_VEL 3.5

class MMS {
  public:
  uint8_t SPD_L = 0;
  uint8_t SPD_R = 0;
  int CURRENT_L = 0;
  int CURRENT_R = 0;

  // PID variables
  float PID = 0;
  float P = 0;
  float I = 0;
  float D = 0;

  // Emergency STOP of motors by torque disable and zero spd
  void brake_motors(){;}

  // Set speed of motors by linear and angular velocity
  void set_spd(float linear, float angular){
    
    // Torque enable
    digitalWrite(TRQ1,HIGH);    
    digitalWrite(TRQ2,HIGH);

    // Calculate velocity to speed of each wheel
    SPD_L = int(linear - angular * BASE_WIDTH / 2.0);
    SPD_R = int(linear + angular * BASE_WIDTH / 2.0);

    // Set the spinning direction of each wheel
    if(SPD_L > 0){
      digitalWrite(DIR1A,HIGH); digitalWrite(DIR1B,LOW);
    }
    if(SPD_L < 0){
     digitalWrite(DIR1A,LOW); digitalWrite(DIR1B,HIGH);
   }
    if(SPD_R > 0){
     digitalWrite(DIR2A,HIGH); digitalWrite(DIR2B,LOW);
    }
    if(SPD_R < 0){
      digitalWrite(DIR2A,LOW); digitalWrite(DIR2B,HIGH);
    }
  
    analogWrite(PWM1, abs(SPD_L));  
    analogWrite(PWM2, abs(SPD_R));
}
};






void setup(){

  Serial.begin(9600);
  /*Left motor*/
  pinMode(PWM1,OUTPUT);
  pinMode(DIR1A,OUTPUT);
  pinMode(DIR1B,OUTPUT);
  pinMode(TRQ1,OUTPUT);
  pinMode(CUR1,INPUT);
  
  /*Right motor*/
  pinMode(PWM2,OUTPUT);
  pinMode(DIR2A,OUTPUT);
  pinMode(DIR2B,OUTPUT);
  pinMode(TRQ2,OUTPUT);
  pinMode(CUR2,INPUT);
 
  /*Encoders*/
  /*pinMode(EN1A, INPUT_PULLUP);
  pinMode(EN1B, INPUT_PULLUP);
  pinMode(EN2A, INPUT_PULLUP);
  pinMode(EN2B, INPUT_PULLUP);*/
 }


 
 






  void loop() {
    digitalWrite(TRQ1,HIGH);    
    digitalWrite(TRQ2,HIGH);
    
    /*digitalWrite(DIR1A,HIGH); 
    digitalWrite(DIR1B,LOW);
    digitalWrite(DIR2A,HIGH); 
    digitalWrite(DIR2B,LOW);

    analogWrite(PWM1, 100);
    analogWrite(PWM2, 100);

    delay(5000);

    digitalWrite(DIR1A,LOW); 
    digitalWrite(DIR1B,HIGH);
    digitalWrite(DIR2A,LOW); 
    digitalWrite(DIR2B,HIGH);    

    analogWrite(PWM1, 100);
    analogWrite(PWM2, 100);
    
    delay(5000);*/

    digitalWrite(DIR1A,HIGH); 
    digitalWrite(DIR2A,LOW);
    analogWrite(PWM1, 100);
    digitalWrite(DIR1B,HIGH); 
    digitalWrite(DIR2B,LOW);
    analogWrite(PWM2, 100);
    Serial.print(analogRead(CUR1));
    Serial.print("  ");
    Serial.println(analogRead(CUR2));
    
    delay(2000);

    digitalWrite(DIR1A,LOW); 
    digitalWrite(DIR2A, HIGH);
    analogWrite(PWM1, 100);
    digitalWrite(DIR1B,LOW); 
    digitalWrite(DIR2B,HIGH);
    analogWrite(PWM2, 100);

    Serial.print(analogRead(CUR1));
    Serial.print("  ");
    Serial.println(analogRead(CUR2));
    
    delay(2000);

}
