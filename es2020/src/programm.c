#include "programm.h"
#include "joystick.h"
#include "rng.h"
#include "lcd.h"
#include "systick.h"
#include <stm32l073xx.h>

//Display Texts
const char* text_prg1 = 		("Alarm! Wach auf!"
		       	   	     	 	 "<Beep Beep Beep>");
const char* text_prg_joy = 		("Stop den Alarm! "
		       	   	     	 	 "---<Joystick>---");
const char* text_prg_touch =	("Stop den Alarm! "
		       	   	       	   	 "----<Touch>-----");
const char * text_richtig = 	("    Richtig!    "
	   	 	  	  	  	  	     "--<Alarm aus!>--");
const char * text_falsch = 		("    Falsch!     "
			   	 	  	  	  	 "<Beep Beep Beep>");
const char* text_diffi =		("Schwierigkeit:  "
		       	   	          	 "     .:| |:.    ");

//LCD Codes for displaying "Arrows"
const char left 	= 0x7F;
const char right 	= 0x7E;
const char up 		= 0x5E;
const char down 	= 0x76;

/* Displays single Arrow Symbol on Display
 * Using 2 LSB as Coding (masked)
 * */
static void display_arrow( uint8_t two_bit_number){
	two_bit_number = two_bit_number & 0x3;
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

/* Displays 16 Arrows (one row) on LCD
 * 2 Bits equals one Arrow
 * */
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

/* Shapes joystick input in two-bit encoded arrow direction number
 * */
static uint8_t to_two_bit_number(struct joystick_d input){
	uint8_t tbn = 0;
	if (input.x < 0) {tbn = 0;}
	if (input.x > 0) {tbn = 1;}
	if (input.y < 0) {tbn = 2;}
	if (input.y > 0) {tbn = 3;}
	return tbn;
}

/* Main Joystick program
 * Gets a random number an displays it as Arrows on LCD
 * Reads joystick input and compares it with displayed Arrows until matched
 * Wrong input causes reset
 * */
static void joystick_prg(void){
	_Bool reset = 1;
	uint32_t rn; 		// random number for arrow pattern
	uint32_t mask; 		// so only input gets compared
	uint32_t input; 	// joystick input concatenated
	uint8_t pos; 		// current position in input and rn
	uint8_t tbn = 0; 	// current read two bit number (arrow)

	do{
		if (reset){
			reset = 0;
			pos = 0;
			input = 0;
			mask = 0xfffffffc;
			rn = get_rng();
			//reduce rn length based on difficulty

			display_arrows(rn);
		}
		tbn = to_two_bit_number(get_joy_xy_poll());
		display_arrow(tbn);
		input =  input | (tbn << pos);
		if (pos != 0) {mask = (mask << 2);}
		pos ++;
		pos ++;
		if (input != (rn & ~mask)){
			reset = 1;
			lcd_set_cursor(1, 15);
			lcd_print_char(0xFE);
			lcd_print_string(text_falsch);
			delay_ms(2500);
		}
	}while(input != rn);
	lcd_print_string(text_richtig);
	delay_ms(2500);
}

/* Main Alarm program
 * Shows generic LCD output
 * Start subprogram depending on chosen device in settings
 * */
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
	//Display Difficulty
	lcd_print_string(text_diffi);
	lcd_set_cursor(1, 8);
	lcd_print_char(get_difficulty()+ 0x31);
	//Remove blinking Cursor
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
