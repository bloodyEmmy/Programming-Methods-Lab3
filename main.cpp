/**
 * @file main.cpp
 * @brief Точка входа в программу. Запуск генерации, тестов и бенчмарков.
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include "structures.h"
#include "generators.h"
#include "statistics.h"
#include "chisquare.h"

using namespace std;
using namespace std::chrono;

/**
 * @brief Экспортирует сгенерированные матрицы в текстовый файл для тестов NIST.
 * @param data Двумерный вектор (матрица) с результатами генерации.
 * @param filename Имя выходного файла (например, "method1.txt").
 */
void export_to_file(const vector<vector<unsigned int>>& data, const string& filename) {
    ofstream out(filename);
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            out << data[i][j] << " ";
        }
        out << "\n";
    }
    out.close();
}

/**
 * @brief Замеряет время выполнения заданного алгоритма генерации.
 * @param method Номер метода (1 - LCG, 2 - LFSR, 3 - Xorshift*, 4 - std::rand).
 * @param count Количество чисел для генерации (объем выборки).
 * @param base_seed Стартовое значение (seed) для инициализации состояния.
 * @return Время выполнения в микросекундах.
 */
long long measure_time(int method, int count, unsigned int base_seed) {
    auto start = high_resolution_clock::now();

    if (method == 1) {
        LCG_State state; state.current_value = base_seed;
        for (int i = 0; i < count; ++i) my_custom_lcg(state);
    } 
    else if (method == 2) {
        LFSR_State state; state.lfsr_value = base_seed; state.counter = 0;
        for (int i = 0; i < count; ++i) my_hybrid_lfsr(state);
    } 
    else if (method == 3) {
        Xorshift_State state; state.state = base_seed;
        for (int i = 0; i < count; ++i) my_xorshift_star(state);
    } 
    else if (method == 4) {
        srand(base_seed);
        for (int i = 0; i < count; ++i) rand();
    }

    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

/**
 * @brief Главная функция программы. 
 * Управляет логикой вызова всех подпрограмм.
 * @return 0 при успешном завершении.
 */
int main() {
    unsigned int base_seed = time(NULL);

    vector<vector<unsigned int>> selections_method1(20, vector<unsigned int>(1000));
    vector<vector<unsigned int>> selections_method2(20, vector<unsigned int>(1000));
    vector<vector<unsigned int>> selections_method3(20, vector<unsigned int>(1000));
    
    LCG_State state1; state1.current_value = base_seed;
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 1000; ++j) selections_method1[i][j] = my_custom_lcg(state1);

    LFSR_State state2; state2.lfsr_value = base_seed; state2.counter = 0;
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 1000; ++j) selections_method2[i][j] = my_hybrid_lfsr(state2);

    Xorshift_State state3; state3.state = base_seed;
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 1000; ++j) selections_method3[i][j] = my_xorshift_star(state3);
    cout << "1. Генерация завершена." << endl;

    cout << "\n2. Базовая статистика (выборка 0):" << endl;
    SampleStats stats1 = calculate_stats(selections_method1[0]);
    cout << "LCG: Среднее=" << stats1.mean << " | Откл=" << stats1.std_deviation << " | CV=" << stats1.coef_variation << "%" << endl;
    SampleStats stats2 = calculate_stats(selections_method2[0]);
    cout << "LFSR: Среднее=" << stats2.mean << " | Откл=" << stats2.std_deviation << " | CV=" << stats2.coef_variation << "%" << endl;
    SampleStats stats3 = calculate_stats(selections_method3[0]);
    cout << "Xorshift*: Среднее=" << stats3.mean << " | Откл=" << stats3.std_deviation << " | CV=" << stats3.coef_variation << "%" << endl;

    cout << "\n3. Проверка Хи-квадрат (из 20 выборок):" << endl;
    int unif1 = 0, unif2 = 0, unif3 = 0;
    int indep1 = 0, indep2 = 0, indep3 = 0;
    double thresh_u = 16.919, thresh_i = 123.2;

    for (int i = 0; i < 20; ++i) {
        if (calculate_chi_square_uniformity(selections_method1[i]) < thresh_u) unif1++;
        if (calculate_chi_square_uniformity(selections_method2[i]) < thresh_u) unif2++;
        if (calculate_chi_square_uniformity(selections_method3[i]) < thresh_u) unif3++;
        
        if (calculate_chi_square_independence(selections_method1[i]) < thresh_i) indep1++;
        if (calculate_chi_square_independence(selections_method2[i]) < thresh_i) indep2++;
        if (calculate_chi_square_independence(selections_method3[i]) < thresh_i) indep3++;
    }
    cout << "LCG: Равномерность " << unif1 << "/20 | Случайность " << indep1 << "/20" << endl;
    cout << "LFSR: Равномерность " << unif2 << "/20 | Случайность " << indep2 << "/20" << endl;
    cout << "Xorshift*: Равномерность " << unif3 << "/20 | Случайность " << indep3 << "/20" << endl;

    export_to_file(selections_method1, "method1.txt");
    export_to_file(selections_method2, "method2.txt");
    export_to_file(selections_method3, "method3.txt");
    cout << "\n4. Файлы для тестов NIST сохранены." << endl;

    cout << "\n5. Запуск замеров скорости..." << endl;
    vector<int> sizes = {1000, 10000, 100000, 1000000};
    ofstream out("benchmark.csv");
    out << "Size,LCG,LFSR,Xorshift,StandardRand\n"; 

    for (int size : sizes) {
        long long t1 = measure_time(1, size, base_seed);
        long long t2 = measure_time(2, size, base_seed);
        long long t3 = measure_time(3, size, base_seed);
        long long t4 = measure_time(4, size, base_seed); 

        out << size << "," << t1 << "," << t2 << "," << t3 << "," << t4 << "\n";
        cout << "Обработан объем: " << size << " элементов." << endl;
    }
    out.close();
    cout << "Файл benchmark.csv успешно создан!" << endl;

    return 0;
}