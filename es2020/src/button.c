#include "button.h"
#include <stm32l073xx.h>
#include <stddef.h>
#include <stdbool.h>

//setup for Button Module
void button_setup(void){
	/*should connect to Connector D4 on extension board
	 *D4 resolves to: D4-->PB5 and D5-->PB4
	 */

	//enable Clock for GPIO
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

	//set GPIO mode for PB4 and PB5 to input mode (mode 0)
	GPIOB->MODER = (GPIOB->MODER
			& ~(GPIO_MODER_MODE4_Msk | GPIO_MODER_MODE5_Msk))
			| ((00 << GPIO_MODER_MODE4_Pos) & GPIO_MODER_MODE4_Msk)
			| ((00 << GPIO_MODER_MODE5_Pos) & GPIO_MODER_MODE5_Msk);
}

//Returns 1 if Button_0 is currently pressed else 0
bool read_button_0(void){
	return GPIO_IDR_ID4_Pos >> (GPIOB->IDR & (GPIO_IDR_ID4_Msk));
}

//Returns 1 if Button_1 is currently pressed else 0
bool read_button_1(void){
	return GPIO_IDR_ID5_Pos >> (GPIOB->IDR & (GPIO_IDR_ID5_Msk));
}


