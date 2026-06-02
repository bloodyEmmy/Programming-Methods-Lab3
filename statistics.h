#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

struct SampleStats {
    double mean;           // Среднее значение
    double std_deviation;  // Среднеквадратичное отклонение
    double coef_variation; // Коэффициент вариации (в процентах)
};

SampleStats calculate_stats(const std::vector<unsigned int>& sample);

#endif