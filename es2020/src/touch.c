#include "touch.h"
#include "delay.h"
#include "i2c.h"
#include <stm32l0xx.h>

#define TOUCH_I2C_ADDRESS 0x5b
#define TOUCH_CH1_CH7_OFFSET = 0x00
#define THRESHOLD_REG_START_ADDR            0X41
#define TOUCH_BASELINE_OFFSET = 			0x1e
//#define TOUCH_BASELINE_VALUE =
#define DEBOUNCE_REG_ADDR                   0X5B
#define FILTER_AND_GLOBAL_CDC_CFG_ADDR      0X5C
#define FILTER_AND_GLOBAL_CDT_CFG_ADDR      0X5D
#define ELEC_CFG_REG_ADDR                   0X5E

#define FILTERED_DATA_REG_START_ADDR_L      0X04

void touch_init(void){
// Stopmodus setzen über 0x00 in ECR Reg
	uint8_t write_buffer[2] = {ELEC_CFG_REG_ADDR, 0x00};
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
// Setze Schwellwert für Drücken und lösen   0x0808
//	write_buffer[1] = 0x08; // Defaultwert für Schwelle
//	for(int i=0;i<CHANNEL_NUM;i++)
//	    {
//		write_buffer[0] = THRESHOLD_REG_START_ADDR+2*i;  // Druck Schwelle
//		i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 2, NULL, 0);
//		write_buffer[0] = THRESHOLD_REG_START_ADDR+2*i+1; // Release Schwelle
//		i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 2, NULL, 0);
//	    }
//	write_buffer[0] = ELEC_CFG_REG_ADDR;
//	write_buffer[1] = 0x3c;
//	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 2, NULL, 0);
// Run mode setzen
	write_buffer[0] = ELEC_CFG_REG_ADDR;
	write_buffer[1] = 0x3c;
	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 2, NULL, 0);
}



uint8_t getTouchInfo(void){
	volatile uint8_t  isTouched[2]={ 0, 0};
	// Lese Touch 0-3 aus
	uint8_t write_buffer = 0x00;
	//uint8_t write_buffer = 0x00;
	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 1, NULL, 0);
	i2c_transfer(TOUCH_I2C_ADDRESS, NULL, 0, isTouched[0], 1);
	// Lese Touch 8-11 aus
	write_buffer = 0x01;
	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 1, NULL, 0);
	i2c_transfer(TOUCH_I2C_ADDRESS, NULL, 0, isTouched[1], 1);
	isTouched[1] = isTouched[1]<<4; // Kanäle 8-12 in obberes Nibble verschieben
	isTouched[0] = isTouched[0] & 0x0F; // unteres Nibble maskieren
	isTouched[0] = isTouched[0] + isTouched[1];
	return isTouched[0];
}

uint8_t getTouchDetail(uint8_t channel){
	uint16_t read_buffer = 0;
	uint8_t write_buffer = FILTERED_DATA_REG_START_ADDR_L+channel;
	i2c_transfer(TOUCH_I2C_ADDRESS, write_buffer, 1, NULL, 0);
	i2c_transfer(TOUCH_I2C_ADDRESS, NULL, 0, read_buffer, 1);
	return read_buffer;
}




