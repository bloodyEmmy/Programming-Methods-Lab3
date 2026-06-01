#ifndef STRUCTURES_H
#define STRUCTURES_H

struct LCG_State {
    unsigned int current_value;
};

// ТЕБЕ НУЖНО ДОБАВИТЬ ЭТО:
struct LFSR_State {
    unsigned int lfsr_value; 
    unsigned int counter;    
};

#endif