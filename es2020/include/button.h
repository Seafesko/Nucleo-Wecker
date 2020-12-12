#ifndef BUTTON_H_
#define BUTTON_H_

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

//setup for Button Module
//should connect to Connector D4 on extension board
//D4 resolves to: D4-->PB5 and D5-->PB4
void button_setup(void);

_Bool read_button_0(void);
_Bool read_button_1(void);

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_H_ */
