#include "clock.h"
#include "systick.h"
#include "button.h"
#include "i2c.h"
#include "lcd.h"
#include <stm32l073xx.h>

int main(void) {

	//INIT
	clock_setup_16MHz();
	systick_setup();
	i2c_setup();
	lcd_init();
	button_setup();
	lcd_print_string("White --> Alarm!"
	                 "Blue --> Setting");
	//MAIN
	while (1) {
		if (read_button_0()) {
			//call Alarm Clock subprocess
			lcd_print_string("    Button 0    "
						     "    Test!       ");
		}else if(read_button_1()) {
			//call settings subprocess
			lcd_print_string("    Button 1    "
							 "    Test!       ");
		}else {
			lcd_print_string("White --> Alarm!"
			                 "Blue --> Setting");
		}
		delay_ms(50); //else Display refreshes too often
	}
}
