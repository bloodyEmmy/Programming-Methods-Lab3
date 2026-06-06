#include "structures.h"

unsigned int my_custom_lcg(LCG_State& state) {
    unsigned long long a = 1103515245;
    unsigned long long c = 12345;
    unsigned long long m = 2147483648; // 2 ^ 31

    unsigned long long next_state = (a * state.current_value + c) % m;
    state.current_value = next_state;
    unsigned int shifted = next_state >> 15; 
    unsigned int result = next_state ^ shifted;
    return result % 10000;
}

unsigned int my_hybrid_lfsr(LFSR_State& state) {
    for (int k = 0; k < 32; ++k) {
        unsigned int new_bit = ((state.lfsr_value >> 31) ^ 
                                (state.lfsr_value >> 21) ^ 
                                (state.lfsr_value >> 1) ^ 
                                state.lfsr_value) & 1;

        state.lfsr_value = (state.lfsr_value >> 1) | (new_bit << 31);
    }
    state.counter = state.counter + 1;
    unsigned int result = state.lfsr_value + state.counter;
    return result % 10000;
}

unsigned int my_xorshift_star(Xorshift_State& state) {
    unsigned int x = state.state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state.state = x;
    unsigned int result = x * 2685821657u;
    return result % 10000;
}