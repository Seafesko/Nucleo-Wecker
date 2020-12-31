#include "programm.h"
#include "joystick.h"
#include "rng.h"
#include "lcd.h"
#include "systick.h"
#include <stm32l073xx.h>

//Display Texts
const char* text_prg1 = 		("Alarm! Wach auf!"
		       	   	     	 	 "Beep Beep Beep  ");
const char* text_prg_joy = 		("Stop den Alarm! "
		       	   	     	 	 "---<Joystick>---");
const char* text_prg_touch =	("Stop den Alarm! "
		       	   	       	   	 "----<Touch>-----");
const char* text_diffi =		("Schwierigkeit:  "
		       	   	          	 "     .:| |:.    ");

const char left 	= 0x7F;
const char right 	= 0x7E;
const char up 		= 0x5E;
const char down 	= 0x76;

static void display_arrow( uint8_t two_bit_number){
	switch (two_bit_number) {
	case 0:
		lcd_print_char(down);
		break;
	case 1:
		lcd_print_char(up);
		break;
	case 2:
		lcd_print_char(right);
		break;
	case 3:
		lcd_print_char(left);
		break;
	default:
		lcd_print_char(down);
	}
	delay_ms(250);
}

static void display_arrows( uint32_t rn)
{
	uint8_t two_bit_number;
	uint32_t mask_2bit = 0x3;
	uint16_t shift = 0;
	do{
		two_bit_number = (rn >> shift) & mask_2bit;
		display_arrow(two_bit_number);
		shift ++;
		shift ++;
	}while(shift != 32);
}

static uint8_t to_two_bit_number(struct joystick_d input){
	uint8_t tbn = 0;
	if (input.x < 0) {tbn = 0;}
	if (input.x > 0) {tbn = 1;}
	if (input.y < 0) {tbn = 2;}
	if (input.y > 0) {tbn = 3;}
	return tbn;
}

static void joystick_prg(void){
	_Bool reset = 1;
	uint32_t rn;
	uint32_t mask;
	uint32_t input = 0;
	uint16_t count = 0;
	uint8_t tbn = 0;

	do{
		if (reset){
			reset = 0;
			mask = ~0;
			rn = get_rng();
			display_arrows(rn);
		}
		tbn = to_two_bit_number(get_joy_xy_poll());
		display_arrow(tbn);
		input =  input | (tbn << count);
		count ++;
		count ++;
		mask = (mask << count);
		mask = mask | 0;
		if (input != (rn & ~mask)){
			reset = 1;
			count = 0;
			lcd_set_cursor(2, 16);
			lcd_print_string(" Fehler !        "
			   	       	  	 " Nochmal!        ");
			delay_ms(2500);
		}
	}while(input != rn);
	lcd_print_string(("Richtig !!!     "
 	       	   	 	  "----<Touch>-----"));
	delay_ms(2500);
}

void programm (void){
	//Initial LCD
		lcd_print_string(text_prg1);
		delay_ms(2500);
		uint8_t device = get_device();
		switch (device ) {
		case 0:
			lcd_print_string(text_prg_joy);
			break;
		case 1:
			lcd_print_string(text_prg_touch);
			break;
		}
		delay_ms(2500);
		lcd_print_string(text_diffi);
		lcd_set_cursor(1, 8);
		lcd_print_char(get_difficulty()+ 0x31);
		//Removes blinking Cursor
		lcd_set_cursor(1, 15);
		lcd_print_char(0xFE);
		delay_ms(2500);

		switch (device ) {
		case 0:
			joystick_prg();
			break;
		case 1:
			lcd_print_string(text_prg_touch);
			break;
		}
}
