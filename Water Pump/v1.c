#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define ledred 11
#define ledgreen 12
#define relay 10
#define in 2

ISR (INT0_vect){

	PORTB |= (1<<PB3);

	_delay_ms(1000);

	//relay off
    PORTB |= (1<<PB2);
}

int main(){

	//declare output
	DDRB |= (1<<PB2); //relay
	DDRB |= (1<<PB3); //red
	DDRB |= (1<<PB4); //green

	//declare input
	DDRD &= ~(1<<PD2);

	//interrupt @ the raising edge
    EICRA |= (1<<ISC01);
    EICRA |= (1<<ISC00);

    sei();
    EIMSK |= (1<<INT0);

    //relay on
    PORTB = PORTB &~(1<<PB2);
    _delay_ms(500);

    //on led green
    PORTB |= (1<<PB4);

    //10min delay
    int i;
    for(i=0;i<10;i++) _delay_ms(60000);

    //relay off
    PORTB |= (1<<PB2);

	return 0;
}