#include "rng.h"
#include <stm32l073xx.h>

void rng_setup(void){
	//enable Clock for Timer 6
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	//enable Timer 6
	TIM6->CR1 = TIM_CR1_CEN;
}

//https://en.wikipedia.org/wiki/Xorshift
/* The state word must be initialized to non-zero */
static uint32_t xorshift32(uint32_t state)
{
	uint32_t x = state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return x;
}

 uint32_t get_rng(void){
	uint32_t seed = TIM6->CNT;
	if (seed == 0)
	{
		seed = 0x15; //something != 0
	}
	return xorshift32(seed);
}


