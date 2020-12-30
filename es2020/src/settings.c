#include <stm32l073xx.h>
#include "joystick.h"
#include "button.h"
#include "systick.h"
#include "lcd.h"

//Display Texts
const char* text_settings = ("    Settings    "
		       	   	    "                ");
const char* text_help = ("Use Joystick!   "
		       	   	     "Return w/ White ");
const char* diffi_l = ("Schwierigkeit:  "
	       	   	      " [1]   2    3   ");
const char* diffi_m = ("Schwierigkeit:  "
	       	   	      "  1   [2]   3   ");
const char* diffi_h = ("Schwierigkeit:  "
	       	   	      "  1    2   [3]  ");

const char* device_j = ("Geraeteauswahl: "
	       	   	        "[Joystick] Touch");
const char* device_t = ("Geraeteauswahl: "
	       	   	        "Joystick [Touch]");

const char* touch = ("Touch Test:     "
	       	   	     "1?2?3?4?5?6?7?8?");

const char* joy_a = ("Joystick analog:"
	       	   	     "todo: optional  ");

/*internal globals*/
static uint8_t difficulty = 0;
static uint8_t device = 0;

/* internal functions */
static void add_diffi(void){
	difficulty ++;
	if (difficulty >2) {difficulty = 0;}
}

static void sub_diffi(void){
	difficulty --;
	if (difficulty >2) {difficulty = 2;}
}

static void add_device(void){
	device ++;
	if (device >1) {device = 0;}
}

static void sub_device(void){
	device --;
	if (device >1) {device = 1;}
}

static uint8_t add_setting(uint8_t setting_pos){
	setting_pos ++;
	if (setting_pos >3) {setting_pos = 0;}
	return setting_pos;
}

static uint8_t sub_setting(uint8_t setting_pos){
	setting_pos --;
	if (setting_pos >3) {setting_pos = 3;}
	return setting_pos;
}

static void choose_diff(int8_t joy_d_y){
	const char* difficulties [3] = { diffi_l, diffi_m, diffi_h};
	if(joy_d_y >= 1) {sub_diffi();}
	else if(joy_d_y <= -1) {add_diffi();}
	lcd_print_string(difficulties[difficulty]);
	delay_ms(100);
}

static void choose_device(int8_t joy_d_y){
	const char* devices [2] = { device_j, device_t};
	if(joy_d_y >= 1) {sub_device();}
	else if(joy_d_y <= -1) {add_device();}
	lcd_print_string(devices[device]);
	delay_ms(100);
}

static void test_touch(void){
	lcd_print_string(touch);
	delay_ms(100);
}

static void test_joy(void){
	lcd_print_string(joy_a);
	delay_ms(100);
}


/* external functions */

uint8_t get_difficulty(void){
	return difficulty;
}

uint8_t get_device(void){
	return device;
}

uint16_t settings(void){
	/*Button 0 returns to Main */
	/*Joystick for navigating Menu*/
	/*Display Options on LCD*/
	/*stores Settings in internal global*/
	/*can be read by getter method*/

	uint8_t setting_pos = 0;
	struct joystick_d joy_d;
	_Bool joy_action;

	//Initial LCD
	lcd_print_string(text_settings);
	delay_ms(1500);
	lcd_print_string(text_help);
	delay_ms(1500);
	choose_diff(0);

	do {
		joy_action = 0;

		// Polling on Inputs
		do {
			joy_d = read_joystick_d();
			joy_action = joy_d.x + joy_d.y + joy_d.b;
			delay_ms(100);

			//Return to Main Menu if White Button is pressed
			if (read_button_0()) {
				delay_ms(200);
				return 0;
			};
		} while (!joy_action);


		//Change Setting to Display by changing setting_pos depending on Joystick Input
		if		(joy_d.x >=  1) {setting_pos = sub_setting(setting_pos);}
		else if	(joy_d.x <= -1) {setting_pos = add_setting(setting_pos);}

		//Display
		switch (setting_pos ) {
		case 0:
			choose_diff(joy_d.y);
			break;
		case 1:
			choose_device(joy_d.y);
			break;
		case 2:
			test_touch();
			break;
		case 3:
			test_joy();
			break;
		}
	}while(1);
}


