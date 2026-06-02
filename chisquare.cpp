#include "chisquare.h"

double calculate_chi_square_uniformity(const std::vector<unsigned int>& sample) {
    // Создаем 10 корзин и заполняем их нулями
    std::vector<int> buckets(10, 0);
    
    // 1. Распределяем числа по корзинам
    for (int i = 0; i < sample.size(); ++i) {
        // Делим на 1000, чтобы получить индекс от 0 до 9
        // Например, 4567 / 1000 = 4. Значит, число идет в 5-ю корзину (индекс 4).
        int index = sample[i] / 1000;
        
        // Защита от выхода за пределы массива (если вдруг число равно 10000)
        if (index >= 10) {
            index = 9;
        }
        
        buckets[index]++;
    }
    
    // 2. Считаем значение Хи-квадрат
    double chi_square = 0.0;
    double expected = sample.size() / 10.0; // Ожидаемое значение для каждой корзины (100)
    
    for (int i = 0; i < 10; ++i) {
        double diff = buckets[i] - expected;
        chi_square += (diff * diff) / expected;
    }
    
    return chi_square;
}

double calculate_chi_square_independence(const std::vector<unsigned int>& sample) {
    // Создаем матрицу 10x10, заполненную нулями
    std::vector<std::vector<int>> matrix(10, std::vector<int>(10, 0));
    
    // Идем по массиву с шагом 2, чтобы брать непересекающиеся пары (x1, x2), (x3, x4)
    int pairs_count = sample.size() / 2;
    for (int i = 0; i < sample.size() - 1; i += 2) {
        int row = sample[i] / 1000;
        int col = sample[i + 1] / 1000;
        
        // Защита от выхода за границы массива
        if (row >= 10) row = 9;
        if (col >= 10) col = 9;
        
        matrix[row][col]++;
    }
    
    // Считаем Хи-квадрат по матрице
    double chi_square = 0.0;
    double expected = pairs_count / 100.0; // 500 пар / 100 ячеек = 5
    
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            double diff = matrix[i][j] - expected;
            chi_square += (diff * diff) / expected;
        }
    }
    
    return chi_square;
}