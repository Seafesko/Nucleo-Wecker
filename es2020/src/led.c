#include <led.h>
#include <stm32l073xx.h>
#include <stdbool.h>

bool led_is_on = false;
bool Led_Is_active = false;
void TIM7_Init(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN; // Clock aktivieren
	TIM7->CR1 = TIM_CR1_CEN; // Timer enable
	TIM7->DIER |= TIM_DIER_UIE; // Interruptbetrieb aktivieren
	//TIM7->CR2 = TIM_CR2_MMS_2;
	//Timer auf 500 ms stellen
	TIM7->PSC = 0x4000; // ~16000
	TIM7->ARR = 0x200; // ~500
}
void TIM7_IRQHandler(void){
	TIM7->SR &= ~TIM_SR_UIF; //Clean UIF Flag
	if(Led_Is_active){
		led_toggle();
	}
}

void led_setup(void){
	/*should connect to Connector D2 on extension board
	 *D2 resolves to: D2-->PA10
	 */

	//enable Clock for GPIO
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

	//set GPIO mode for PA10 to output mode (mode 01)
	GPIOA->MODER = (GPIOA->MODER
			& ~(GPIO_MODER_MODE10_Msk)) | ((01 << GPIO_MODER_MODE10_Pos) & GPIO_MODER_MODE10_Msk);
	// Output_Type_Register

	// Defaults lassen
	//GPIOB->OTYPER = (GPIOB->OTYPER
	//		& ~(GPIO_OT_OT10_Msk)) | ((1 << GPIO_MODER_MODE10_Pos) & GPIO_MODER_MODE10_Msk);
	// PullUpDownRegister (10 fuer Pull_Down)
	GPIOA->PUPDR = (GPIOA->PUPDR
				& ~(GPIO_PUPDR_PUPD10_Msk)) | ((10 << GPIO_PUPDR_PUPD10_Pos) & GPIO_PUPDR_PUPD10_Msk);
	// SPEED Reg -> Defaultwerte lassen
}

void led_on(void){
	led_is_on = true;
	GPIOA->ODR = (GPIOA->ODR
			& ~(GPIO_ODR_OD10_Msk)) | ((1 << GPIO_ODR_OD10_Pos) & GPIO_ODR_OD10_Msk);
}
void led_off(void){
	led_is_on = false;
	GPIOA->ODR = (GPIOA->ODR
			& ~(GPIO_ODR_OD10_Msk)) | ((0 << GPIO_ODR_OD10_Pos) & GPIO_ODR_OD10_Msk);
}
void led_toggle(void){
	if(led_is_on){
		led_off();
	}
	else{
		led_on();
	}
}
void led_status(bool status){
	Led_Is_active = status;
}
