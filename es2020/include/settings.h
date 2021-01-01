#ifndef SETTINGS_H_
#define SETTINGS_H_

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

/* external functions */

uint8_t get_difficulty(void);
uint8_t get_device(void);
uint8_t get_end_pos(void);
uint16_t settings(void);

#ifdef __cplusplus
}
#endif

#endif /* SETTINGS_H_ */
