#ifndef CHISQUARE_H
#define CHISQUARE_H

#include <vector>

double calculate_chi_square_uniformity(const std::vector<unsigned int>& sample);
double calculate_chi_square_independence(const std::vector<unsigned int>& sample);

#endif