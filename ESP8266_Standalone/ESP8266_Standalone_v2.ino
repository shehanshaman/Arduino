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
//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial
#define Relay1            D6
#define Relay2            D5
#define reset_state       D4
#define Connection        D7

#include <EEPROM.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <WiFiManager.h>  

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "8000fc09e23f49c68325e4d7c2c718f2";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "SLT_FIBRE";
//char pass[] = "shehan123456";

void blynking(int val){
   for (int i = 0; i <= 3; i++) {
    digitalWrite(reset_state, LOW);
    delay(val);
    digitalWrite(reset_state, HIGH);
    delay(val);
   }
}

BLYNK_CONNECTED() {
  // Request Blynk server to re-send latest values for all pins
  Blynk.syncAll();
  Serial.println("Request Blynk server to re-send latest values");
}

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
  digitalWrite(Relay2, pinValue);
  Serial.print("VO: ");
  Serial.print(pinValue);
  Serial.println();
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // process received value
  digitalWrite(Relay1, pinValue);
  Serial.print("V1: ");
  Serial.print(pinValue);
  Serial.println();
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  delay(1000);
  pinMode(Connection, OUTPUT);
  pinMode(reset_state, OUTPUT);

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  
  digitalWrite(reset_state, HIGH);
//  Flash button for reset wifi data
  pinMode(0, INPUT_PULLUP); 

  WiFiManager wifiManager;

  int count = 1;

  while(count){
    count++;
    if(digitalRead(0) == 0){
      blynking(200);
      wifiManager.resetSettings();
      count = 0;
    }
    delay(200);
    if(count > 15){
      count = 0;
    }
  }
  
  wifiManager.autoConnect("Google Home");
  
  digitalWrite(Connection, HIGH);
  
  Blynk.config(auth);
  digitalWrite(Connection, LOW);
}

void loop()
{
  Blynk.run();
}
