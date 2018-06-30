#include <IRremote.h>

int IRpin = 8;
IRrecv irrecv(IRpin);
decode_results results;

unsigned  int value;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() 
{
  if (irrecv.decode(&results)) 
    {  value = results.value;
      Serial.println(value); // Print the Serial 'results.value'
      delay(100);
      irrecv.resume();   // Receive the next value
    }
}

