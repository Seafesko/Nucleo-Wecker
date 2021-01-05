#include <stm32l073xx.h>
#include "settings.h"
#include "joystick.h"
#include "button.h"
#include "systick.h"
#include "lcd.h"
#include "touch.h"

//Display Texts
const char* text_settings 	=  ("    Settings    "
								"                ");
const char* text_help 		=  ("Use Joystick!   "
								"Return w/ White ");
const char* diffi_l 		=  ("Schwierigkeit:  "
								" [1]   2    3   ");
const char* diffi_m 		=  ("Schwierigkeit:  "
								"  1   [2]   3   ");
const char* diffi_h 		=  ("Schwierigkeit:  "
								"  1    2   [3]  ");
const char* device_j 		=  ("Geraeteauswahl: "
								"[Joystick] Touch");
const char* device_t 		=  ("Geraeteauswahl: "
								"Joystick [Touch]");
const char* touch 			=  ("Touch ch12345678"
								"Test:          ");
const char* joy_test 		=  ("Joystick Test:  "
								"Push Joystick   ");
const char* joy_analog 		=  ("X:              "
								"Y:              ");

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
	uint8_t touch_zustaende [8];
	getTouchData(touch_zustaende);
	for (uint8_t i=0;i<8;i++){
		lcd_set_cursor(1, 8+i);
		char zeichen = (touch_zustaende[i]+ 0x30);
		lcd_print_char(zeichen);
	}
	delay_ms(100);
}

static void itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
}

static void display_joy_a(struct joystick_a joy_a){
	char x_vaule [4];
	char y_vaule [4];

	lcd_clear_display();
	lcd_print_char('X');
	lcd_print_char(':');
	lcd_print_char(0xFE);
	if(joy_a.x < 1000) {lcd_print_char(0xFE);}
	itoa(joy_a.x, x_vaule);
	lcd_print_string(x_vaule);

	lcd_set_cursor(1, 0);
	lcd_print_char('Y');
	lcd_print_char(':');
	lcd_print_char(0xFE);
	lcd_print_char(0xFE);
	itoa(joy_a.y, y_vaule);
	lcd_print_string(y_vaule);
}

static void test_joy(_Bool joy_button){
	lcd_print_string(joy_test);
	delay_ms(100);
	if (joy_button)
	{
		_Bool joy_action;
		struct joystick_a joy_a;
		joy_action = 0;

		do {
		// Polling on Inputs
		do {
			joy_a = read_joystick_a();
			joy_action = joy_a.x + joy_a.y;
			delay_ms(100);
		} while (!joy_action);
		//Display x and y
		lcd_print_string(joy_analog);
		display_joy_a(joy_a);
		}while(joy_a.x < 1000); // till joy button
	delay_ms(750);
	lcd_clear_display();
	lcd_print_string(joy_test);
	}
}


/* external functions */

uint8_t get_difficulty(void){
	return difficulty;
}

uint8_t get_end_pos(void){
	uint8_t end_pos;
	switch (difficulty) {
		case 0:
			end_pos = 8;
			break;
		case 1:
			end_pos = 16;
			break;
		case 2:
			end_pos = 32;
			break;
		default:
			end_pos = 32;
	}
	return end_pos;
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
			test_joy(joy_d.b);
			break;
		}
	}while(1);
}


