#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

//setup for Button Module
//should connect to Connector D4 on extension board
//D4 resolves to: D4-->PB5 and D5-->PB4
void joystick_setup(void);
uint16_t read_joystick(void);

#ifdef __cplusplus
}
#endif

#endif /* JOYSTICK_H_ */
