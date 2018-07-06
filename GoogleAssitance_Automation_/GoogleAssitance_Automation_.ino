#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#include <EEPROM.h>
 
#include <ESP8266WiFi.h>

#define Relay1            D6
#define Relay2            D5

#define led               D7

#define WLAN_SSID       "My wire"             // Your SSID
#define WLAN_PASS       "shehan123456"        // Your password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "shehanshaman"            // Replace it with your username
#define AIO_KEY         "575d1067ab434b53bfe90e6094fe5204"   // Replace with your Project Auth Key

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/


// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/light1"); // FeedName
Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/light2");
Adafruit_MQTT_Subscribe LightAll = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/allon");

void MQTT_connect();

void lastState(){
  Serial.println();
  
  Serial.print("Relay 1 :");
  Serial.print(EEPROM.read(0));
  Serial.println();

  Serial.print("Relay 2 :");
  Serial.print(EEPROM.read(1));
  Serial.println();
  
  if(EEPROM.read(0) == 1){
    digitalWrite(Relay1,LOW);
  }else{
    digitalWrite(Relay1,HIGH);
  }

  if(EEPROM.read(1) == 1){
    digitalWrite(Relay2,LOW);
  }else{
    digitalWrite(Relay2,HIGH);
  }
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);

  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);

  lastState();
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  digitalWrite(led,LOW);

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&Light1);
  mqtt.subscribe(&Light2);
  mqtt.subscribe(&LightAll);
}

void loop() {
 
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &Light1) {
      Serial.print("Light 1 > ");
      Serial.print(F("Got: "));
      Serial.println((char *)Light1.lastread);
      byte Light1_State = atoi((char *)Light1.lastread);
      digitalWrite(Relay1, !Light1_State);
      EEPROM.write(0, Light1_State);
      EEPROM.commit();
      //Serial.println(EEPROM.read(0));
      //Serial.println(Light1_State);
    }
    if (subscription == &Light2) {
      Serial.print("Light 2 > ");
      Serial.print(F("Got: "));
      Serial.println((char *)Light2.lastread);
      byte Light2_State = atoi((char *)Light2.lastread);
      digitalWrite(Relay2, !Light2_State);
      EEPROM.write(1, Light2_State);
      EEPROM.commit();
      //Serial.println(EEPROM.read(1));
      //Serial.println(Light2_State);
    }
    if (subscription == &LightAll) {
      Serial.print("Light all > ");
      Serial.print(F("Got: "));
      Serial.println((char *)LightAll.lastread);
      byte Light_State = atoi((char *)LightAll.lastread);
      digitalWrite(Relay1, !Light_State);
      digitalWrite(Relay2, !Light_State);
      
      EEPROM.write(0, Light_State);
      EEPROM.write(1, Light_State);
      EEPROM.commit();
    }
  }
   
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    //Serial.println("Connected");
    return;
  }

  digitalWrite(led,HIGH);
  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      //while (1);
      Serial.println("Wait 10 min to reconnect");
      delay(600000);
    }
  }
  Serial.println("MQTT Connected!");
  digitalWrite(led,LOW);
}
