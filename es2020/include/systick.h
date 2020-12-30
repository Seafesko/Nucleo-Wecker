#ifndef SYSTICK_H_
#define SYSTICK_H_

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

// configures the system tick to generate an interrupt every millisecond
void systick_setup(void);
void delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_H_ */
