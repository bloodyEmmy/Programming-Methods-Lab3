#include <iostream>
#include <vector>
#include <ctime>
#include "structures.h"

#include "generators.h"

using namespace std;

int main() {
    // Матрица для первого метода
    vector<vector<unsigned int>> selections_method1(20, vector<unsigned int>(1000));
    // Матрица для второго метода
    vector<vector<unsigned int>> selections_method2(20, vector<unsigned int>(1000));
    
    // --- Инициализация и запуск МЕТОДА 1 ---
    LCG_State state1;
    state1.current_value = time(NULL);

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 1000; ++j) {
            selections_method1[i][j] = my_custom_lcg(state1);
        }
    }

    // --- Инициализация и запуск МЕТОДА 2 ---
    LFSR_State state2;
    state2.lfsr_value = time(NULL); // Стартовое значение трубы зависит от времени
    state2.counter = 0;             // Кликер начинаем с нуля

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 1000; ++j) {
            selections_method2[i][j] = my_hybrid_lfsr(state2);
        }
    }
    
    cout << "Данные для двух методов успешно сгенерированы!" << endl;
    return 0;
}