#include "clock.h"
#include "systick.h"
#include "button.h"
#include "i2c.h"
#include "lcd.h"
#include "joystick.h"
#include "settings.h"
#include <stm32l073xx.h>



int main(void) {

	//INIT
	clock_setup_16MHz();
	systick_setup();
	i2c_setup();
	lcd_init();
	button_setup();
	joystick_setup();

	//Display Texts
	const char* text_b0 = ("    Button 0    "
		       	   	       "    Test!       ");
	const char* text_b1 = ("    Button 1    "
		       	   	       "    Test!       ");
	const char* text_main = ("White --> Alarm!"
            				 "Blue --> Setting");

	_Bool button_press;
	_Bool button_0;
	_Bool button_1;

	//MAIN
	while (1) {
		lcd_print_string(text_main);

		button_press = 0;
		button_0 = 0;
		button_1 = 0;

		while(!button_press){
			button_0 = read_button_0();
			button_1 = read_button_1();
			button_press = button_0 + button_1;
			delay_ms(20);
		}

		if (button_0) 		{
			//TODO: call Alarm Clock subprocess here
			lcd_print_string(text_b0);
			delay_ms(1000); //Displays for 1 second
		}
		else if (button_1) 	{settings();}
		else 				{lcd_print_string(text_main);}
	}
}
