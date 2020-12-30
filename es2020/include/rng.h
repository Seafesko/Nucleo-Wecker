#ifndef RNG_H_
#define RNG_H_

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

/* external functions */

void rng_setup(void);
uint32_t get_rng(void);


#ifdef __cplusplus
}
#endif

#endif /* RNG_H_ */
