#ifndef SETTINGS_H_
#define SETTINGS_H_

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

//internal functions
static void add_diffi(void);
static void sub_diffi(void);
static void add_device(void);
static void sub_device(void);
static uint8_t add_setting(uint8_t setting_pos);
static uint8_t sub_setting(uint8_t setting_pos);
static void choose_diff(int8_t joy_d_y);
static void choose_device(int8_t joy_d_y);
static void test_touch(void);
static void test_joy(void);

/* external functions */
uint8_t get_difficulty(void);
uint8_t get_device(void);
uint16_t settings(void);

#ifdef __cplusplus
}
#endif

#endif /* SETTINGS_H_ */
