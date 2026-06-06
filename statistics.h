/**
 * @file statistics.h
 * @brief Расчет базовых статистических метрик для выборки.
 */

#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

/**
 * @brief Структура для хранения результатов статистического анализа.
 */
struct SampleStats {
    double mean;           ///< Математическое ожидание (среднее значение)
    double std_deviation;  ///< Среднеквадратичное (стандартное) отклонение
    double coef_variation; ///< Коэффициент вариации в процентах
};

/**
 * @brief Вычисляет базовую статистику для вектора данных.
 * @param sample Константная ссылка на вектор псевдослучайных чисел.
 * @return Структура SampleStats с вычисленными метриками.
 */
SampleStats calculate_stats(const std::vector<unsigned int>& sample);

#endif // STATISTICS_H