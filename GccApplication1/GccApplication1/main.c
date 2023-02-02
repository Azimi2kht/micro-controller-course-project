#define  F_CPU 8000000
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "motor.h"

#define TRIGGER 7
#define ECHO 6 
#define MAX_DISTANCE 20
#define DELAY 60

#define KEY_PRT PORTD
#define KEY_DDR	DDRD
#define KEY_PIN	PIND
#define MODE_PIN 4

int t1;
int t2;
long int distance;
int state=0;


void show_distance() {
	if (distance < 0)
	{
	 	distance += 141;
	}
	char str[17];
	sprintf(str, " Distance: %dcm", distance);
	lcd_command(CMD_CLEAR);
	lcd_print(str);	
}

void cap_init(){
	TCCR1A =0x00;
	TCCR1B = 0x41;
}

ISR (TIMER1_CAPT_vect){
	if (state==0) {
		t1=ICR1;
		TCCR1A =0x00;
		TCCR1B=0x02;
		state=1;
	} else {
		t2=ICR1;
		distance= t2-t1;
		distance /= 58;
		show_distance();
		if (PIND & (1 << MODE_PIN)) {
			if (distance < MAX_DISTANCE) {
				motor_turn(1);
			} else { 
				motor_move();
			}
		} 
		TCCR1A =0x00;
		TCCR1B=0x42;
		state=0;
		trigger_for_ultrasound();
	}
}

void trigger_for_ultrasound(){
	PORTD =0xff;
	_delay_ms(DELAY);
	PORTD= 0x7f;
}

void ultrasound_init() {
    DDRD |= (1<<TRIGGER);
	PORTD |= (1 << MODE_PIN);
	DDRC = 0xff;
}

int main(void) {
	motor_init();
	lcd_init();
	ultrasound_init();
	cap_init();
	trigger_for_ultrasound();
	TIMSK = (1<<TICIE1);
	sei();
    while (1) 
    {
		if (~PIND & (1 << MODE_PIN)) {
			// keypad	
		} 		
    }
}

