#ifndef STRUCTURES_H
#define STRUCTURES_H

struct LCG_State {
    unsigned int current_value;
};

struct LFSR_State {
    unsigned int lfsr_value; 
    unsigned int counter;    
};

struct Xorshift_State {
    unsigned int state;
};

#endif