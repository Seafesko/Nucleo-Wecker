#include "touch.h"
#include "delay.h"
#include "i2c.h"
#include <stm32l0xx.h>

void touch_setup(void){
	setRegister(SOFT_RESET,0x63);
// Stopmodus setzen durch 0x00 in ECR Reg
	setRegister(ELEC_CFG_REG_ADDR,0);
	delay_ms(100);

// Setze Globale Parameter
	setRegister(FILTER_AND_GLOBAL_CDC_CFG_ADDR,0x10);
	setRegister(FILTER_AND_GLOBAL_CDT_CFG_ADDR,0x20);

// Setze Debounce
	setRegister(DEBOUNCE_REG_ADDR,0x22);

// Setze AutoConfig_Reg
	setRegister(AUTO_CONFIG_CONTROL_REG_0,0x23);
	setRegister(AUTO_CONFIG_CONTROL_REG_USL,0xc8);
	setRegister(AUTO_CONFIG_CONTROL_REG_LSL,0x80);
	setRegister(AUTO_CONFIG_CONTROL_REG_TL,0xb4);

// Setze Schwellwert fï¿½r Drï¿½cken und lï¿½sen   0x0808
	for(int i=0;i<CHANNEL_NUM;i++)
	{
		setRegister(THRESHOLD_REG_START_ADDR+2*i,0x10); // Druck Schwelle
		setRegister(THRESHOLD_REG_START_ADDR+2*i+1,0x08); // Release Schwelle
	}
// Run mode setzen
	setRegister(ELEC_CFG_REG_ADDR,0x0c);// 0x3c empfohlen
}
static void setRegister(uint8_t reg, uint8_t data){
	uint8_t write_buffer[2] = {reg, data};
	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 2, NULL, 0);
}

// Gibt 10 Bit gefilterte Daten des ADC für einen beliebigen Kanal zurueck
uint16_t getTouchDetail(uint8_t channel){
	uint8_t read_buffer[2] = {0};
	uint8_t write_buffer[1] = {FILTERED_DATA_REG_START_ADDR_L+2*channel};

	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer[1], 1, read_buffer[0], 1);
	write_buffer[1] = FILTERED_DATA_REG_START_ADDR_H+2*channel;
	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer[1], 1, read_buffer[1], 1);
	uint16_t data = read_buffer[0]+(read_buffer[1]<<8);
	return data | 0x03FF; // ´Nichtbenutzte Bits zu 0 setzen
}

void getTouchData(uint8_t *dataPtr){
	uint8_t write_buffer[1] = {TOUCH_STATUS_REG_ADDR_L};
	uint8_t dataBuffer[2] = {0};

	i2c_transfer(TOUCH_I2C_ADDRESS,write_buffer[0], 1, dataBuffer[0], 1); // Kanal 0 bis 7 auslesen
	write_buffer[0] = TOUCH_STATUS_REG_ADDR_H;
	i2c_transfer(TOUCH_I2C_ADDRESS,write_buffer, 1,dataBuffer[1], 1);// Kanal 8 bis 11 auslesen
	dataBuffer[0] &=0x0F;
	dataBuffer[1] = dataBuffer[1] << 4;
	uint8_t tmp = dataBuffer[0] | dataBuffer[1];

	for (uint8_t i=0;i<8;i++){
		dataPtr[i] = (tmp & (0x01 <<i))>>i;
	}
}
