#include "joystick.h"
#include <stm32l073xx.h>

//setup for Button Module
void joystick_setup(void){
	/*should connect to Connector A3 on extension board
	 *A3 resolves to: A3-->PB0 and A4-->PC1
	 */

	//enable Clock for GPIO
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

	//set GPIO mode for PB0 to analog mode (mode 11)
	GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODE0_Msk ))
			| ((11 << GPIO_MODER_MODE0_Pos) & GPIO_MODER_MODE0_Msk);

	//set GPIO mode for PC1 to analog mode (mode 11)
	GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODE1_Msk ))
			| ((11 << GPIO_MODER_MODE1_Pos) & GPIO_MODER_MODE1_Msk);



	//ADC
	//calibrate
	/*The internal analog calibration is kept if the ADC is disabled (ADEN=0) or if the ADC voltage reference is disabled (ADVREGEN = 0).*/
	if ((ADC1->CR & ADC_CR_ADEN)==0)//Calibration can only be initiated when the ADC is disabled (when ADEN=0)
	{
		// calibrate Calibration setting bit ADCAL=1
		ADC1->CR = (ADC1->CR & ~(ADC_CR_ADCAL_Msk ))
		| ((1 << ADC_CR_ADCAL_Pos) & ADC_CR_ADCAL_Msk);
		while((ADC1->CR & ADC_CR_ADCAL)==1) //It is then cleared by hardware as soon the calibration completes.
		{
			//waiting for calibration complete
		}
	}

	//ADC Settings
	/*Channel Selection */
	if ((ADC1->CR & ADC_CR_ADSTART == 0)) //only allowed when ADSTART=0
	{
		ADC1->CHSELR = (ADC1->CHSELR
				& ~(ADC_CHSELR_CHSEL3_Msk | ADC_CHSELR_CHSEL4_Msk))
				| ((1 << ADC_CHSELR_CHSEL3_Pos) & ADC_CHSELR_CHSEL3_Msk)
				| ((1 << ADC_CHSELR_CHSEL4_Pos) & ADC_CHSELR_CHSEL4_Msk);
	}
	return;
}

uint16_t read_joystick(void){
	//ADC enable sequence example
	/* (1) Clear the ADRDY bit */
	/* (2) Enable the ADC */
	/* (3) Wait until ADC ready */
	ADC1->ISR |= ADC_ISR_ADRDY;/* (1) */
	ADC1->CR |= ADC_CR_ADEN;/* (2) */
	if((ADC1->CFGR1 & ADC_CFGR1_AUTOFF)==0)
	{
		int i;
		while((ADC1->ISR & ADC_ISR_ADRDY)==0)/* (3) */
		{
			delay_ms(50);
			i++;
			if (i>100){
				break;
			}
		}
	}

	uint16_t result = ADC1->DR;
	delay_ms(5);
	return result;
}
