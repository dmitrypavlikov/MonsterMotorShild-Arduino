#include "MMS/MMS.cpp"

MMS mms;

void setup(){
  mms.start();
  Serial.begin(9600);
}

  void loop() {
    /*mms.set_spd(0.5, 0.0);
    delay(1000);*/
    mms.set_spd(3.0, 0.0);
    delay(4000);
    /*mms.set_spd(-0.5, 0.0);
    delay(1000);*/
    mms.set_spd(-3.0, 0.0);
    delay(4000);

}
