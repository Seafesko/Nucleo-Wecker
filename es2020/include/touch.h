#ifndef TOUCH_H_
#define TOUCH_H_

#define CHANNEL_NUM   12
#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

void touch_setup(void);
uint16_t getTouchDetail(uint8_t channel);
void getTouchData(uint8_t *dataPtr);
static void setRegister(uint8_t reg, uint8_t data);

#ifdef __cplusplus
}
#endif
/*These two registers indicate the detected touch/release status of all of the 12 sensing input channels*/
#define TOUCH_STATUS_REG_ADDR_L             0X00
#define TOUCH_STATUS_REG_ADDR_H             0X01

/*The MPR121 provides filtered electrode output data for all 12 channels*/
/*Total 26 registers,for 12 channel electrode out put data.Each channel corresponding two registers:high byte and low byte*/
/*0x04~0x1d*/
#define FILTERED_DATA_REG_START_ADDR_L      0X04
#define FILTERED_DATA_REG_START_ADDR_H      0X05

/*Along with the 10-bit electrode filtered data output, each channel also has a 10-bit baseline value*/
/*0X1E~0X2A*/
#define BASELINE_VALUE_REG_START_ADDR             0X1E

/*All12 of the electrode baseline values are controlled by the same set of filtering control registers, 0x2B ~ 0x35*/
/*The 13th channel ELEPROX is controlled by registers 0x36 ~ 0x40*/
#define BASELINE_FILTERING_CONTROL_REG_START_ADDR    0X2B

/*0X5F-0X6B*/
#define ELEC_CHARGE_CURRENT_REG_START_ADDR  0X5F

#define TOUCH_I2C_ADDRESS 0x5b
#define THRESHOLD_REG_START_ADDR            0X41
#define DEBOUNCE_REG_ADDR                   0X5B
#define FILTER_AND_GLOBAL_CDC_CFG_ADDR      0X5C
#define FILTER_AND_GLOBAL_CDT_CFG_ADDR      0X5D
#define ELEC_CFG_REG_ADDR                   0X5E

#define FILTERED_DATA_REG_START_ADDR_L      0X04
#define AUTO_CONFIG_CONTROL_REG_0		    0X7B
#define AUTO_CONFIG_CONTROL_REG_1		    0X7C
#define AUTO_CONFIG_CONTROL_REG_USL		    0X7D
#define AUTO_CONFIG_CONTROL_REG_LSL		    0X7E
#define AUTO_CONFIG_CONTROL_REG_TL		    0X7F

#define SOFT_RESET						    0X80
#endif
