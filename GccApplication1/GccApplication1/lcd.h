#ifndef INCFILE1_H_
#define INCFILE1_H_


#define LCD_DPRT PORTA
#define LCD_DDDR DDRA
#define LCD_DPIN PINA

#define LCD_CPRT PORTB
#define LCD_CDDR DDRB
#define LCD_CPIN PINB
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

#define CMD_CLEAR 0x01
#define CMD_LTOR 0x06
#define CMD_DP_ON_CR_ON 0x0E
#define CMD_DP_ON_CR_BL 0x0F


void lcd_command(unsigned char cmd) {
	LCD_DPRT = cmd;
	LCD_CPRT &= ~(1 << LCD_RS);
	LCD_CPRT &= ~(1 << LCD_RW);
	LCD_CPRT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_CPRT &= ~(1 << LCD_EN);
	_delay_us(100);
}

void lcd_data(unsigned char data) {
	LCD_DPRT = data;
	LCD_CPRT |= (1 << LCD_RS);
	LCD_CPRT &= ~(1 << LCD_RW);
	LCD_CPRT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_CPRT &= ~(1 << LCD_EN);
	_delay_us(100);
}

void lcd_goto(unsigned char x) {
	unsigned char firstCharAddr = 0x80;
	lcd_command(firstCharAddr + x - 1);
	_delay_us(100);
}

void lcd_print(char *str) {
	unsigned char i = 0;
	while (str[i] != 0) {
		lcd_data(str[i]);
		i++;
	}
}

void lcd_print_digit(unsigned char ch) {
	lcd_data(ch);
}

void lcd_init() {
	LCD_DDDR = 0xFF;
	LCD_CDDR = 0xFF;
	
	LCD_CPRT &= ~(1 << LCD_EN);
	
	_delay_us(2000);
	
	lcd_command(CMD_DP_ON_CR_ON);
	lcd_command(CMD_CLEAR);
	
	_delay_us(2000);
	
	lcd_command(CMD_LTOR);
}

#endif /* INCFILE1_H_ */