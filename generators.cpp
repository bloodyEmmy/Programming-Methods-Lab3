#include "structures.h"

unsigned int my_custom_lcg(LCG_State& state) {
    // 1. Задаем константы (тип long long, чтобы при умножении не обрезалось число)
    unsigned long long a = 1103515245;
    unsigned long long c = 12345;
    unsigned long long m = 2147483648; // Это 2 в 31 степени

    // 2. Считаем новое значение по классической формуле LCG
    unsigned long long next_state = (a * state.current_value + c) % m;
    
    // Обновляем состояние в нашей структуре для следующего вызова
    state.current_value = next_state;

    // 3. Наша модификация (скремблинг старших битов с младшими)
    // Сдвигаем вправо на 15 позиций
    unsigned int shifted = next_state >> 15; 
    
    // Делаем XOR
    unsigned int result = next_state ^ shifted;

    // 4. В задании сказано: разброс выборки не менее 5000.
    // Берем остаток от 10000. Теперь алгоритм всегда будет 
    // выдавать числа от 0 до 9999.
    return result % 10000;
}

// Наш второй, гибридный метод
unsigned int my_hybrid_lfsr(LFSR_State& state) {
    // 1. "Смотрим на шарики": берем 31, 21, 1 и 0 биты. 
    // Значок ^ (XOR) сравнивает их.
    // & 1 в конце отсекает всё лишнее, оставляя нам в руке ровно один новый "шарик" (0 или 1).
    unsigned int new_bit = ((state.lfsr_value >> 31) ^ 
                            (state.lfsr_value >> 21) ^ 
                            (state.lfsr_value >> 1) ^ 
                            state.lfsr_value) & 1;

    // 2. "Двигаем трубу и кладем шарик":
    // (state.lfsr_value >> 1) сдвигает все вправо (старый выпадает).
    // (new_bit << 31) ставит наш новый бит в самый левый край.
    // Значок | (ИЛИ) склеивает их вместе.
    state.lfsr_value = (state.lfsr_value >> 1) | (new_bit << 31);

    // 3. "Щелкаем кликером": обычная арифметика (+1)
    state.counter = state.counter + 1;

    // 4. Смешиваем логику трубы и математику счетчика, чтобы сломать предсказуемость
    unsigned int result = state.lfsr_value + state.counter;

    // 5. Ограничиваем диапазон, чтобы числа были от 0 до 9999 (как требует задание)
    return result % 10000;
}