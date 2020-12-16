#include "clock.h"
#include "systick.h"
#include "button.h"
#include "i2c.h"
#include "lcd.h"
#include "joystick.h"
#include <stm32l073xx.h>

int main(void) {

	//INIT
	clock_setup_16MHz();
	systick_setup();
	i2c_setup();
	lcd_init();
	button_setup();
	//joystick_setup();


	//Display Texts
	const char* text_b0 = ("    Button 0    "
		       	   	       "    Test!       ");
	const char* text_b1 = ("    Button 1    "
		       	   	       "    Test!       ");
	const char* text_main = ("White --> Alarm!"
            				 "Blue --> Setting");

	//Display Main Menu Text
	lcd_print_string(text_main);

	//MAIN
	while (1) {
		if (read_button_0()) {
			//TODO: call Alarm Clock subprocess here
			lcd_print_string(text_b0);
		}else if(read_button_1()) {
			//TODO: put all settings subprocess here
			lcd_print_string(text_b1);
		}else {
			lcd_print_string(text_main);
		}
		delay_ms(75); //else Display refreshes too often
	}
}
