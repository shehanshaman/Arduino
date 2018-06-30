#include <IRremote.h>

int RECV_PIN = 8; // the pin where you connect the output pin of TSOP4838
int wait = 200;

IRrecv irrecv(RECV_PIN);
decode_results results;

void checkIrValue(){
	if (irrecv.decode(&results)) {
    unsigned int value = results.value;
    
    if(value == r1_l1 || value == r2_l1 || value == r3_l1){
         if(itsONled[0] == 1) {
            digitalWrite(LIGHT1, HIGH);
            Serial.println("1 off");
            itsONled[0] = 0;
            delay(wait);
            EEPROM.write(1, 0);
         } else {
             digitalWrite(LIGHT1, LOW);
             Serial.println("1 on");
             delay(wait);
             itsONled[0] = 1;
             EEPROM.write(1, 1);
         }
    }else if(value == r1_l2 || value == r2_l2 || value == r3_l2){
         if(itsONled[1] == 1) {
            digitalWrite(LIGHT2,HIGH);
            Serial.println("2 off");
            delay(wait);
            itsONled[1] = 0;
            EEPROM.write(2, 0);
         } else {
             digitalWrite(LIGHT2,LOW);
             Serial.println("2 on");
             delay(wait);
             itsONled[1] = 1;
             EEPROM.write(2, 1);
         }
    }else if(value == r1_l3 || value == r2_l3 || value == r3_l3){
         if(itsONled[2] == 1) {
            digitalWrite(LIGHT3, HIGH);
            Serial.println("3 off");
            delay(wait);
            itsONled[2] = 0;
            EEPROM.write(3, 0);
         } else {
             digitalWrite(LIGHT3,LOW);
             Serial.println("3 on");
             delay(wait);
             itsONled[2] = 1;
             EEPROM.write(3, 1);
         }
    }else if(value == r1_l4 || value == r2_l4 || value == r3_l4){
          if(itsONled[3] == 1) {
            digitalWrite(LIGHT4,HIGH);
            Serial.println("4 off");
            delay(wait);
            itsONled[3] = 0;
            EEPROM.write(4, 0);
         } else {
             digitalWrite(LIGHT4,LOW);
             itsONled[3] = 1;
             Serial.println("4 on");
             delay(wait);
             EEPROM.write(4, 1);
         }
    }else if(value == on){
      if(isMissed){
        digitalWrite(13,LOW);
        EEPROM.write(0, 0);
        Serial.println("Misssed call off"); 
        isMissed = 0;        
      }else{
        digitalWrite(13,HIGH);
        EEPROM.write(0, 1);
        Serial.println("Misssed call on"); 
        isMissed = 1;
      }
    }
    Serial.println(value);
    //Serial.println("Error");
    delay(100);
    irrecv.resume(); // Receive the next value
  }
}
