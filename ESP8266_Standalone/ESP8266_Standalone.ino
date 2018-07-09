/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define Relay1            D6
#define Relay2            D5

#include <EEPROM.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "8000fc09e23f49c68325e4d7c2c718f2";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "My wire";
char pass[] = "shehan123456";

void lastState(){
  Serial.println();
  
  Serial.print("Relay 1 :");
  Serial.print(EEPROM.read(12));
  Serial.println();

  Serial.print("Relay 2 :");
  Serial.print(EEPROM.read(14));
  Serial.println();
  
  if(EEPROM.read(12) == 1){
    digitalWrite(Relay1,LOW);
  }else{
    digitalWrite(Relay1,HIGH);
  }

  if(EEPROM.read(14) == 1){
    digitalWrite(Relay2,LOW);
  }else{
    digitalWrite(Relay2,HIGH);
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  EEPROM.begin(512);
  lastState();
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

