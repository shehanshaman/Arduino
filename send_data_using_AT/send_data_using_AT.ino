  
#include <SoftwareSerial.h>
 
//SIM808 TX is connected to Arduino D7
#define SIM808_TX_PIN 7
 
//SIM808 RX is connected to Arduino D6
#define SIM808_RX_PIN 6
 
//Create software serial object to communicate with SIM808
SoftwareSerial serialSIM808(SIM808_TX_PIN,SIM808_RX_PIN);

 char id[16];// = "24";
 char value [16];// = "24";

  int numId = 1,numValue = 100;

void gsm_disConnect_gprs(){
  serialSIM808.write("AT+CGATT=0\r\n"); // Attach to GPRS
  delay(2000);
  Serial.println("GPRS off");
}
  
void gsm_connect_gprs(){
  serialSIM808.write("AT+CGATT=1\r\n"); // Attach to GPRS
  delay(2000);
  serialSIM808.write("AT+SAPBR=1,1\r\n"); // Open a GPRS context
  delay(2000);
  //serialSIM808.write("AT+SAPBER=2,1\r\n");  // To query the GPRS context
  //delay(2000);
  Serial.println("GPRS on");
}


// Function that sends temperature and humidity to my server.
void gsm_send_data(char * id,char * value)
{
    Serial.println("Sending data.");    
    serialSIM808.write("AT+HTTPINIT\r\n");  // Initialize HTTP
    //Serial.print("AT+HTTPINIT\r\n");
    delay(1000);
    //serialSIM808.write("AT+HTTPPARA=\"URL\",\"http://shehanshaman.000webhostapp.com/?id=22&value=23\"\r\n"); // Send PARA command
    serialSIM808.write("AT+HTTPPARA=\"URL\",\"http://shehanshaman.000webhostapp.com/?id=");
    //Serial.print("AT+HTTPPARA=\"URL\",\"http://shehanshaman.000webhostapp.com/?id=");
    delay(50);
    serialSIM808.write(id);   // Add id to the url
    //Serial.print(id);
    delay(50);
    serialSIM808.write("&value="); 
    //Serial.print("&value=");
    delay(50);
    serialSIM808.write(value);   // Add value to url
    //Serial.print(value);
    delay(50);
    serialSIM808.write("\"\r\n");   // close url
   
    //Serial.print("\"\r\n");
    delay(2000);
    serialSIM808.write("AT+HTTPPARA=\"CID\",1\r\n");    // End the PARA
    //Serial.print("AT+HTTPPARA=\"CID\",1\r\n");
    delay(2000);
    serialSIM808.write("AT+HTTPACTION=0\r\n");
    //Serial.print("AT+HTTPACTION=0\r\n");
    delay(3000);    
    serialSIM808.write("AT+HTTPTERM\r\n");
    //Serial.print("AT+HTTPTERM\r\n");
    //Serial.println();
    delay(3000);    
    Serial.print("data sent complete : ");
}

void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  while(!Serial);
   
  //Being serial communication witj Arduino and SIM808
  serialSIM808.begin(9600);
  delay(1000);
   
  Serial.println("Setup Complete!");

  serialSIM808.write("AT+CREG?\r\n");
  delay(150);
 gsm_connect_gprs();



}
 
void loop() {
  //Read SIM808 output (if available) and print it in Arduino IDE Serial Monitor
  if(numId<5){
    itoa(numId, id, 10);
    itoa(numValue,value, 10);
    gsm_send_data(id,value);
    Serial.print(numId);
    Serial.print(" >> ");
    Serial.print(numValue);
    Serial.println();
    delay(2000);
    numId++;
    numValue+=45;
    if(numId==5) gsm_disConnect_gprs();
  }
}
