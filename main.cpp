#include <iostream>
#include <vector>
#include <ctime>
#include "structures.h"
#include "generators.h"

using namespace std;

int main() {
    // Создаем матрицы для трех методов (20 выборок по 1000 элементов)
    vector<vector<unsigned int>> selections_method1(20, vector<unsigned int>(1000));
    vector<vector<unsigned int>> selections_method2(20, vector<unsigned int>(1000));
    vector<vector<unsigned int>> selections_method3(20, vector<unsigned int>(1000));
    
    // Взятие базового времени один раз для инициализации
    unsigned int base_seed = time(NULL);

    // --- МЕТОД 1: LCG ---
    LCG_State state1;
    state1.current_value = base_seed;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 1000; ++j) {
            selections_method1[i][j] = my_custom_lcg(state1);
        }
    }

    // --- МЕТОД 2: Гибридный LFSR ---
    LFSR_State state2;
    state2.lfsr_value = base_seed; 
    state2.counter = 0;             
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 1000; ++j) {
            selections_method2[i][j] = my_hybrid_lfsr(state2);
        }
    }

    // --- МЕТОД 3: Xorshift* ---
    Xorshift_State state3;
    state3.state = base_seed;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 1000; ++j) {
            selections_method3[i][j] = my_xorshift_star(state3);
        }
    }
    
    cout << "Генерация завершена. Данные готовы к анализу." << endl;
    return 0;
}