#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

struct joystick_a {
	uint16_t x, y;
};

struct joystick_d {
	int8_t x, y;
	_Bool b;
};

//setup for Joystick Module
//should connect to Connector A1 on extension board
//A1 resolves to: A0 --> PA0, A1 -->PA1
void joystick_setup(void);
struct joystick_a read_joystick(void);
struct joystick_d read_joystick_d(void);
struct joystick_d analog_to_digital(struct joystick_a joy_ana);
struct joystick_d get_joy_xy_poll(void);

#ifdef __cplusplus
}
#endif

#endif /* JOYSTICK_H_ */
