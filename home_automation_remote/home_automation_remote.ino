#include <EEPROM.h>

//LIGHT pin
#define LIGHT1  9
#define LIGHT2 10
#define LIGHT3 11
#define LIGHT4 12

int itsONled[] = {0,0,0,0};

//remote 1 values
#define r1_l1 8415
#define r1_l2 41055
#define r1_l3 24735
#define r1_l4 4335

//remote 2 values
#define r2_l1 56355
#define r2_l2 15555
#define r2_l3 48195
#define r2_l4 31875

//remote 3 values
#define r3_l1 16
#define r3_l2 2064
#define r3_l3 1040
#define r3_l4 3088

//on and off value
#define on 16575

//missed call is available or not
bool isMissed;

#include "IR.h"

void checkPrev(){
   isMissed = EEPROM.read(0);

   if(isMissed){
    digitalWrite(13,HIGH);
   }

  //LIGHT 1
  if(EEPROM.read(1)==1){
    digitalWrite(LIGHT1,LOW);
    itsONled[0] = 1;
  }else{
    digitalWrite(LIGHT1,HIGH);
  }

  //LIGHT 2
  if(EEPROM.read(2)==1){
    digitalWrite(LIGHT2,LOW);
    itsONled[1] = 1;
  }else{
    digitalWrite(LIGHT2,HIGH);
  }

  //LIGHT 3
   if(EEPROM.read(3)==1){
    digitalWrite(LIGHT3,LOW);
    itsONled[2] = 1;
  }else{
    digitalWrite(LIGHT3,HIGH);
  }

  //LIGHT 4
  if(EEPROM.read(4)==1){
    digitalWrite(LIGHT4,LOW);
    itsONled[3] = 1;
  }else{
    digitalWrite(LIGHT4,HIGH);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   // you can comment this line
  irrecv.enableIRIn();  // Start the receiver

  pinMode(LIGHT1,  OUTPUT);
  pinMode(LIGHT2,  OUTPUT);
  pinMode(LIGHT3,  OUTPUT);
  pinMode(LIGHT4,  OUTPUT);

  pinMode(13,OUTPUT);

  //cheking prev
  checkPrev();

}

void loop() {
  // put your main code here, to run repeatedly:
  checkIrValue();
}
