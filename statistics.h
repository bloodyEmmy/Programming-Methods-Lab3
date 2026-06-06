#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

struct SampleStats {
    double mean;
    double std_deviation;
    double coef_variation;
};

SampleStats calculate_stats(const std::vector<unsigned int>& sample);

#endif