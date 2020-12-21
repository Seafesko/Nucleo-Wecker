#ifndef TOUCH_H_
#define TOUCH_H_

#define CHANNEL_NUM   12
#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

uint8_t getTouchInfo(void);
void touch_init(void);
uint8_t getTouchDetail(uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif
