#include "touch.h"
#include "delay.h"
#include "i2c.h"
#include <stm32l0xx.h>

void touch_setup(void){
// Stopmodus setzen durch 0x00 in ECR Reg
	uint8_t write_buffer[2] = {ELEC_CFG_REG_ADDR, 0};
	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 2, NULL, 0);
	delay_ms(200);
// Setze Globale Parameter
	write_buffer[0] = FILTER_AND_GLOBAL_CDC_CFG_ADDR;
	write_buffer[1] = 0x10;
	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 2, NULL, 0);
	write_buffer[0] = FILTER_AND_GLOBAL_CDT_CFG_ADDR;
	write_buffer[1] = 0x23;
	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 2, NULL, 0);
// Setze Debounce
	write_buffer[0] = DEBOUNCE_REG_ADDR;
	write_buffer[1] = 0x22;
	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 2, NULL, 0);
// Setze Schwellwert fï¿½r Drï¿½cken und lï¿½sen   0x0808
//	write_buffer[1] = 0x08; // Defaultwert fï¿½r Schwelle
//	for(int i=0;i<CHANNEL_NUM;i++)
//	    {
//		write_buffer[0] = THRESHOLD_REG_START_ADDR+2*i;  // Druck Schwelle
//		i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 2, NULL, 0);
//		write_buffer[0] = THRESHOLD_REG_START_ADDR+2*i+1; // Release Schwelle
//		i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 2, NULL, 0);
//	    }
// Run mode setzen
	write_buffer[0] = ELEC_CFG_REG_ADDR;
	write_buffer[1] = 0x3c;
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
	return data | 0x007F; // ´Nichtbenutzte Bits zu 0 setzen
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
