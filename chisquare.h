/**
 * @file chisquare.h
 * @brief Статистические тесты по критерию Пирсона (Хи-квадрат).
 */

#ifndef CHISQUARE_H
#define CHISQUARE_H

#include <vector>

/**
 * @brief Проверка выборки на равномерность распределения.
 * @details Разбивает числа на 10 интервалов и сравнивает их частоты с ожидаемыми (100).
 * Порог для 9 степеней свободы и альфа 0.05 равен 16.919.
 * @param sample Константная ссылка на вектор чисел.
 * @return Вычисленное значение критерия Хи-квадрат.
 */
double calculate_chi_square_uniformity(const std::vector<unsigned int>& sample);

/**
 * @brief Проверка выборки на случайность (сериальный тест пар).
 * @details Исследует независимость соседних элементов, формируя матрицу частот 10x10.
 * Порог для 99 степеней свободы и альфа 0.05 равен 123.2.
 * @param sample Константная ссылка на вектор чисел.
 * @return Вычисленное значение критерия Хи-квадрат.
 */
double calculate_chi_square_independence(const std::vector<unsigned int>& sample);

#endif // CHISQUARE_H