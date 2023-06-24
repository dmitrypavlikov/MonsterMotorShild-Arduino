
/*Left motor*/
#define PWM1    5   //Speed (0-255)
#define DIR1A   7   //Direction CW
#define DIR1B   8   //Direction CWW
#define TRQ1    A0  //Torque (HIGH=Enable)
#define CUR1    A2  //Present Current (0-1023)

/*Right motor*/
#define PWM2    6   //Speed (0-255)
#define DIR2A   4   //Direction CW
#define DIR2B   9   //Direction CWW
#define TRQ2    A1  //Torque (HIGH=Enable)
#define CUR2    A3  //Present Current (0-1023)

/*Encoder settings*/
/*#define EN1A    //TODO
#define EN1B    //TODO
#define EN2A    //TODO
#define EN2B    //TODO
#define */

/*Robot settings*/
#define BASE_WIDTH 0.315
#define MAX_CURRENT 10  //TODO 
#define MAX_VEL 3.5

/*Variables*/
uint8_t SPD_L = 0;
uint8_t SPD_R = 0;
int CURRENT_L = 0;
int CURRENT_R = 0;

float PID = 0;
float P = 0;
float I = 0;
float D = 0;


void setup(){
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


 
 



void brake_motors(){;}

void set_vel(float linear, float angular){
  digitalWrite(TRQ1,HIGH);    //Torque enable
  digitalWrite(TRQ2,HIGH);    //Torque enable
  
  SPD_L = int(linear - angular * BASE_WIDTH / 2.0);
  SPD_R = int(linear + angular * BASE_WIDTH / 2.0);

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
  
  analogWrite(PWM1, SPD_L);
  analogWrite(PWM2, SPD_R);
}

  void loop() {
  // put your main code here, to run repeatedly:

}
