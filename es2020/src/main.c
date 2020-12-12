#include "clock.h"
#include "systick.h"
#include "button.h"
#include "i2c.h"
#include "lcd.h"
#include <stm32l073xx.h>

int main(void) {
	clock_setup_16MHz();
	systick_setup();
	i2c_setup();
	lcd_init();
	button_setup();
	lcd_print_string("    Embedded    "
	                 "    Systems!    ");

	while (1) {
		lcd_print_string("    Embedded    "
			             "    Systems!    ");
		delay_ms(500);

		if (read_button_0()) {
			lcd_print_string("    Button 0    "
						     "    Test!       ");
		}else if(read_button_1() ) {
			lcd_print_string("    Button 1    "
							 "    Test!       ");
		}else {
			lcd_print_string("    Bla         "
				             "    Test!       ");
		}
		delay_ms(500);
	}
}
