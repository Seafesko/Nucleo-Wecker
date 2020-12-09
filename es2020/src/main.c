#include "clock.h"
#include "systick.h"
#include "i2c.h"
#include "lcd.h"
#include <stm32l073xx.h>

int main(void) {
	clock_setup_16MHz();
	systick_setup();
	i2c_setup();
	lcd_init();
	lcd_print_string("    Embedded    "
	                 "    Systems!    ");

	while (1) {
		//Test for commits
		lcd_print_string("    Embedded    "
			                 "    Systems!    ");
		delay_ms(500);
		lcd_print_string("    Bla         "
			                 "    Test!       ");
		delay_ms(500);
	}
}
