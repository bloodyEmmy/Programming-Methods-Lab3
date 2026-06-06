#include "chisquare.h"

double calculate_chi_square_uniformity(const std::vector<unsigned int>& sample) {
    std::vector<int> buckets(10, 0);
    for (int i = 0; i < sample.size(); ++i) {
        int index = sample[i] / 1000;
        if (index >= 10) {
            index = 9;
        }
        buckets[index]++;
    }
    
    double chi_square = 0.0;
    double expected = sample.size() / 10.0;
    for (int i = 0; i < 10; ++i) {
        double diff = buckets[i] - expected;
        chi_square += (diff * diff) / expected;
    }
    
    return chi_square;
}

double calculate_chi_square_independence(const std::vector<unsigned int>& sample) {
    std::vector<std::vector<int>> matrix(10, std::vector<int>(10, 0));
    int pairs_count = sample.size() / 2;
    for (int i = 0; i < sample.size() - 1; i += 2) {
        int row = sample[i] / 1000;
        int col = sample[i + 1] / 1000;
        if (row >= 10) row = 9;
        if (col >= 10) col = 9;
        
        matrix[row][col]++;
    }
    
    double chi_square = 0.0;
    double expected = pairs_count / 100.0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            double diff = matrix[i][j] - expected;
            chi_square += (diff * diff) / expected;
        }
    }
    
    return chi_square;
}