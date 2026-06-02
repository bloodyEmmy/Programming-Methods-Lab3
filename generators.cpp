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

unsigned int my_hybrid_lfsr(LFSR_State& state) {
    // Чтобы получить новое независимое число, прокручиваем "трубу" 32 раза.
    // Это полностью заменит все 32 бита в регистре и уничтожит связь с прошлым числом.
    for (int k = 0; k < 32; ++k) {
        unsigned int new_bit = ((state.lfsr_value >> 31) ^ 
                                (state.lfsr_value >> 21) ^ 
                                (state.lfsr_value >> 1) ^ 
                                state.lfsr_value) & 1;

        state.lfsr_value = (state.lfsr_value >> 1) | (new_bit << 31);
    }

    // Оставляем наш счетчик для дополнительного разрушения линейности
    state.counter = state.counter + 1;

    // Смешиваем полностью обновленный регистр и счетчик
    unsigned int result = state.lfsr_value + state.counter;

    // Ограничиваем диапазон
    return result % 10000;
}

unsigned int my_xorshift_star(Xorshift_State& state) {
    // 1. Копируем текущее состояние для работы
    unsigned int x = state.state;

    // 2. Классические три шага Xorshift (константы 13, 17, 5 подобраны математиками)
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    // 3. Сохраняем обновленное состояние в структуру
    state.state = x;

    // 4. Наша модификация (Xorshift*): нелинейное перемешивание
    // Умножаем на большую константу, чтобы разрушить линейность базового метода
    unsigned int result = x * 2685821657u;

    // 5. Приводим к диапазону до 9999
    return result % 10000;
}