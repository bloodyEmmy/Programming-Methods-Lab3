#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

#include "structures.h"
#include "generators.h"
#include "statistics.h"
#include "chisquare.h"

using namespace std;

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

    cout << "--- Базовая статистика (для первых выборок каждого метода) ---" << endl;
    
    SampleStats stats1 = calculate_stats(selections_method1[0]);
    cout << "Метод 1 (LCG):" << endl;
    cout << "Среднее: " << stats1.mean 
         << " | Отклонение: " << stats1.std_deviation 
         << " | Коэф. вариации: " << stats1.coef_variation << "%" << endl;

    SampleStats stats2 = calculate_stats(selections_method2[0]);
    cout << "Метод 2 (Гибридный LFSR):" << endl;
    cout << "Среднее: " << stats2.mean 
         << " | Отклонение: " << stats2.std_deviation 
         << " | Коэф. вариации: " << stats2.coef_variation << "%" << endl;

    SampleStats stats3 = calculate_stats(selections_method3[0]);
    cout << "Метод 3 (Xorshift*):" << endl;
    cout << "Среднее: " << stats3.mean 
         << " | Отклонение: " << stats3.std_deviation 
         << " | Коэф. вариации: " << stats3.coef_variation << "%" << endl;

    // --- ПРОВЕРКА НА РАВНОМЕРНОСТЬ (ХИ-КВАДРАТ) ДЛЯ ВСЕХ ВЫБОРОК ---
    cout << "--- Проверка на равномерность (20 выборок по каждому методу) ---" << endl;
    double threshold = 16.919;

    int passed_method1 = 0;
    int passed_method2 = 0;
    int passed_method3 = 0;

    for (int i = 0; i < 20; ++i) {
        if (calculate_chi_square_uniformity(selections_method1[i]) < threshold) passed_method1++;
        if (calculate_chi_square_uniformity(selections_method2[i]) < threshold) passed_method2++;
        if (calculate_chi_square_uniformity(selections_method3[i]) < threshold) passed_method3++;
    }

    cout << "Метод 1 (LCG): прошло тестов " << passed_method1 << " из 20." << endl;
    cout << "Метод 2 (Гибридный LFSR): прошло тестов " << passed_method2 << " из 20." << endl;
    cout << "Метод 3 (Xorshift*): прошло тестов " << passed_method3 << " из 20." << endl;

    // --- ПРОВЕРКА НА СЛУЧАЙНОСТЬ (СЕРИАЛЬНЫЙ ТЕСТ) ---
    cout << "--- Проверка на случайность (20 выборок по каждому методу) ---" << endl;
    double threshold_indep = 123.2;

    int indep_passed_method1 = 0;
    int indep_passed_method2 = 0;
    int indep_passed_method3 = 0;

    for (int i = 0; i < 20; ++i) {
        if (calculate_chi_square_independence(selections_method1[i]) < threshold_indep) indep_passed_method1++;
        if (calculate_chi_square_independence(selections_method2[i]) < threshold_indep) indep_passed_method2++;
        if (calculate_chi_square_independence(selections_method3[i]) < threshold_indep) indep_passed_method3++;
    }

    cout << "Метод 1 (LCG): прошло тестов " << indep_passed_method1 << " из 20." << endl;
    cout << "Метод 2 (Гибридный LFSR): прошло тестов " << indep_passed_method2 << " из 20." << endl;
    cout << "Метод 3 (Xorshift*): прошло тестов " << indep_passed_method3 << " из 20." << endl;

    // --- ЭКСПОРТ ДАННЫХ ДЛЯ PYTHON ---
    cout << "--- Сохранение данных в файлы ---" << endl;
    export_to_file(selections_method1, "method1.txt");
    export_to_file(selections_method2, "method2.txt");
    export_to_file(selections_method3, "method3.txt");
    cout << "Файлы method1.txt, method2.txt, method3.txt успешно созданы!" << endl;
    return 0;
}