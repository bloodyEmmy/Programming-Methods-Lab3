#include "statistics.h"
#include <cmath>

SampleStats calculate_stats(const std::vector<unsigned int>& sample) {
    SampleStats result;
    int n = sample.size();
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += sample[i];
    }
    result.mean = sum / n;

    double variance_sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double diff = sample[i] - result.mean;
        variance_sum += diff * diff;
    }
    result.std_deviation = std::sqrt(variance_sum / n);

    if (result.mean != 0) {
        result.coef_variation = (result.std_deviation / result.mean) * 100.0;
    } else {
        result.coef_variation = 0;
    }

    return result;
}