#include "rng.h"
#include <stm32l073xx.h>

void rng_setup(void){
	//enable Clock for RNG
	RCC->AHBENR |= RCC_AHBENR_RNGEN;

	//Buffer used to generate VREFINT reference for the HSI48oscillator switched ON
	SYSCFG->CFGR3 |= SYSCFG_CFGR3_ENREF_HSI48;

	//48 MHz HSI clock ON
	RCC->CRRCR |= RCC_CRRCR_HSI48ON;

	//This bit is set to select the HSI48 clock source for USB and RNG
	RCC->CCIPR |= RCC_CCIPR_HSI48SEL;

	delay_ms(10);
	//enable Random Number Generator
	RNG->CR |= RNG_CR_RNGEN;
}

static uint32_t get_true_rng(void){
	/*To run the RNG in polling mode:
	 * 1.Enable the random number generation by setting the RNGEN bit to “1” in the RNG_CR register.
	 * 2.Read the RNG_SR register and check that:–No error occurred (the SEIS and CEIS bits should be set to ‘0’)
	 * 		A random number is ready (the DRDY bit should be set to ‘1’)
	 * 3.If above conditions are true read the content of the RNG_DR register.
	*/

	/*
	 * Caution:When the CED bit in the RNG_CR register is set to “0”,
	 * the RNG clock frequency must be higher than AHB clock frequency divided by 16,
	 * otherwise the clock checker will flag a clock error (CECS or CEIS in the RNG_SR register)
	 * and the RNG will stop producing random numbers
	 */

	//The content of this register is valid when DRDY=’1’, even if RNGEN=’0
	if ((RNG->SR & (RNG_SR_SEIS | RNG_SR_CEIS)) != 0)
	{
		//Error
		//RNG->SR = (RNG->SR | RNG_SR_CEIS);
		return 0;
	}

	while((RNG->SR & RNG_SR_DRDY)==0)
	{
		/* For robust implementation, add here time-out management */
	}
	return RNG->DR;
}

static uint32_t get_untrue_rng(void){
	uint32_t rn = 1119089326;
	rn = 1119089364;
	return rn;
}

uint32_t get_rng(void){
	uint32_t rn = get_untrue_rng();
	return rn;
}
