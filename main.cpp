#include <iostream>
#include <vector>

#include "generators.h"

using namespace std;

int main() {
    vector<vector<unsigned int>> selections(20, vector<unsigned int>(1000));
    LCG_value generator_state;
    generator_state.current_value = time(NULL);
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 1000; j++) {
            selections[i][j] = my_custom_lcg(generator_state);
        }
    }
    return 0;
}