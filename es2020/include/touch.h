#ifndef TOUCH_H_
#define TOUCH_H_

#define CHANNEL_NUM   12
#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

void touch_init(void);
uint8_t getTouchDetail(uint8_t channel);
void getTouchData(uint8_t *dataPtr);

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


/*Each of the 12 channels can be set with its own set of touch and release thresholds. Touch and release are detected by
comparing the electrode filtered data to the baseline value. typically in the range 0x04~0x10*/
/*Touch condition: Baseline - Electrode filtered data > Touch threshold
  Release condition: Baseline - Electrode filtered data < Release threshold*/
#define THRESHOLD_REG_START_ADDR            0X41

/*All 12 channels use the same set of touch and release debounce numbers.*/
#define DEBOUNCE_REG_ADDR                   0X5B

/*These two registers set the global AFE settings. This includes global electrode charge/discharge current CDC, global charge/
discharge time CDT, as well as a common filtering setting (FFI, SFI, ESI) for all 12 channels, including the 13th Eleprox channel*/
#define FILTER_AND_GLOBAL_CDC_CFG_ADDR      0X5C
#define FILTER_AND_GLOBAL_CDT_CFG_ADDR      0X5D

/*0X5F-0X6B*/
#define ELEC_CHARGE_CURRENT_REG_START_ADDR  0X5F

/*0X6C-0X72*/
#define ELEC_CHARGE_TIME_REG_START_ADDR  0X6C

/*The Electrode Configuration Register (ECR) determines if the MPR121 is in Run Mode or Stop Mode*/
/*Default is 0 to stop mode*/
#define ELEC_CFG_REG_ADDR                    0X5E




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

#endif
