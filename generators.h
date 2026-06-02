#include "structures.h"

#include <vector>

unsigned int my_custom_lcg(LCG_State& value);
unsigned int my_hybrid_lfsr(LFSR_State& state);
unsigned int my_xorshift_star(Xorshift_State& state);