#include <stdio.h>
#include <string.h>

char * addString(char * in, char * out);

int main(int argc, char *argv[]){
	int i=0;
	
	//51
	char cmd0[100] = "avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -o ";
	//cmd 0
	char * cmd = addString(argv[1],cmd0);
	cmd = addString(" ",cmd);
	cmd = addString(argv[1],cmd);
	cmd = addString(".c\0",cmd);


	//cmd1
	char tmp[100] = "avr-objcopy -O ihex -R .eeprom ";
	char * cmd1 = addString(argv[1],tmp);
	cmd1 = addString(" ",cmd1);
	cmd1 = addString(argv[1],cmd1);
	cmd1 = addString(".hex\0",cmd1);

	//cmd2
	char tmp2[100] = "avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:";
	char * cmd2 = addString(argv[1],tmp2);
	cmd2 = addString(".hex\0",cmd2);

	system(cmd);
	system(cmd1);
	system(cmd2);
	/*
	printf("%s\n", cmd);
	printf("%s\n", cmd1);
	printf("%s\n", cmd2);
*/
	return 0;
}

char * addString(char * in, char * out){
	
	int i =0;
	int size = strlen(out);

	for (i=0;i<strlen(in);i++){
		out[size+i] = in[i];
	}

	return out;
}