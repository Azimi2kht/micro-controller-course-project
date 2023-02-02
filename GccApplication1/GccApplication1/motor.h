#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTOR_DDR DDRC
#define MOTOR_PORT PORTC

#define MOTOR_DELAY 2000
#define WHEEL_R 15
#define	WHEELS_DISTANCE 20
#define	PI 3.14
#define	NUM_OF_STEPS (WHEELS_DISTANCE / (2 * WHEEL_R * PI))

int motor_state = 0;

void motor_init() {
	MOTOR_DDR = 0xFF;
}

void motor_move() {
	MOTOR_PORT = 0x99;
	_delay_ms(MOTOR_DELAY);
	MOTOR_PORT = 0xcc;
	_delay_ms(MOTOR_DELAY);
	MOTOR_PORT = 0x66;
	_delay_ms(MOTOR_DELAY);
	MOTOR_PORT = 0x33;
	_delay_ms(MOTOR_DELAY);
}

void motor_turn(int turnRight) {
	if (turnRight) {
		for (int i = 0; i < NUM_OF_STEPS; i++) {
			MOTOR_PORT = 0x09;
			_delay_ms(MOTOR_DELAY);
			MOTOR_PORT = 0x0c;
			_delay_ms(MOTOR_DELAY);
			MOTOR_PORT = 0x06;
			_delay_ms(MOTOR_DELAY);
			MOTOR_PORT = 0x03;
			_delay_ms(MOTOR_DELAY);			
		}
	} else {
		for (int i = 0; i < NUM_OF_STEPS; i++) {
			MOTOR_PORT = 0x90;
			_delay_ms(MOTOR_DELAY);
			MOTOR_PORT = 0xc0;
			_delay_ms(MOTOR_DELAY);
			MOTOR_PORT = 0x60;
			_delay_ms(MOTOR_DELAY);
			MOTOR_PORT = 0x30;
			_delay_ms(MOTOR_DELAY);	
		}
	}	
}

#endif /* MOTOR_H_ */