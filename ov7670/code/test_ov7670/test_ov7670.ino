#include <SD.h>

int CS_Pin = 10;
File myFile;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CS_Pin, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(CS_Pin)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  //myFile = SD.open("test.bmp");
  myFile = SD.open("0.bmp");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
