#include "joystick.h"
#include <stm32l073xx.h>

//setup for Button Module
void joystick_setup(void){

	//enable Clock for GPIO
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

	//set GPIO mode for PA0 and PA1 to analog mode (mode 11)
	GPIOB->MODER = (GPIOB->MODER
			& ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk))
			| ((11 << GPIO_MODER_MODE0_Pos) & GPIO_MODER_MODE0_Msk)
			| ((11 << GPIO_MODER_MODE1_Pos) & GPIO_MODER_MODE1_Msk);

	//enable Clock for ADC
	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;

	// ADC
	// Calibrate
	/* The internal analog calibration is kept if the ADC is disabled (ADEN=0) or if the ADC voltage reference is disabled (ADVREGEN = 0). */
	/* Calibration can only be initiated when the ADC is disabled (when ADEN=0) */
	/* (1) Ensure that ADEN = 0 */
	/* (2) Clear ADEN */
	/* (3) Set ADCAL=1 */
	/* (4) Wait until EOCAL=1 */
	/* (5) Clear EOCAL */
	if((ADC1->CR & ADC_CR_ADEN)!=0)/* (1) */
	{
		ADC1->CR |= ADC_CR_ADDIS;/* (2) */
	}
	ADC1->CR |= ADC_CR_ADCAL;/* (3) */
	while((ADC1->ISR & ADC_ISR_EOCAL)==0)/* (4) */
	{
		/* For robust implementation, add here time-out management */
	}
	ADC1->ISR |= ADC_ISR_EOCAL;/* (5) */

	// ADC selection
	/* (1) Select PCLK by writing 11 in CKMODE */
	/* (2) Select the auto off mode */
	/* (3) Select 10 bit resolution */
	ADC1->CFGR2 |= ADC_CFGR2_CKMODE;/* (1) */
	ADC1->CFGR1 |= ADC_CFGR1_AUTOFF;/* (2) */
	ADC1->CFGR1 = (ADC1->CFGR1 & ~ADC_CFGR1_RES_Msk) | (01 << ADC_CFGR1_RES_Pos);
}

struct joystick_a read_joystick_a(void){
	// Single conversion sequence code example - Software trigger
	ADC1->CHSELR = ADC_CHSELR_CHSEL0;/* Select CHSEL0 */
	/* Performs the AD conversion */
	ADC1->CR |= ADC_CR_ADSTART;/* start the ADC conversion */
	while((ADC1->ISR & ADC_ISR_EOC)==0)/* wait end of conversion */
	{
		/* For robust implementation, add here time-out management */
	}
	uint16_t x = ADC1->DR; /*read Value*/
	ADC1->CHSELR = ADC_CHSELR_CHSEL1;/* Select CHSEL1 */
	ADC1->CR |= ADC_CR_ADSTART;/* start the ADC conversion */
	while((ADC1->ISR & ADC_ISR_EOC)==0)/* wait end of conversion */
	{
		/* For robust implementation, add here time-out management */
	}
	uint16_t y = ADC1->DR;
	struct joystick_a joy_res = { x, y};
	return joy_res;
}

struct joystick_d read_joystick_d(void){
	struct joystick_d res =	analog_to_digital(read_joystick_a());
	return res;
}

struct joystick_d analog_to_digital(struct joystick_a joy_ana){
	_Bool button = 0;
	int8_t x_dig = 0;
	if 		(joy_ana.x > 1000) 	{button = 1;}  //Button Press
	else if	(joy_ana.x < 300) 	{x_dig = 1;}   //x up (to Connector)
	else if (joy_ana.x > 500) 	{x_dig = -1;}  //x down
	else 						{x_dig = 0;}   //x neutral

	int8_t y_dig = 0;
	if 		(joy_ana.y > 1000) 	{button = 1;}  //Button Press
	else if	(joy_ana.y < 300) 	{y_dig = 1;}   //y up (to Connector)
	else if (joy_ana.y > 500) 	{y_dig = -1;}  //y down
	else 						{y_dig = 0;}   //y neutral

	struct joystick_d joy_dig = { x_dig, y_dig, button};
	return joy_dig;
}

