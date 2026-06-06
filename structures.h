/**
 * @file structures.h
 * @brief Заголовочный файл с описанием структур состояний для генераторов.
 * @details Каждая структура хранит внутреннее состояние ("память") 
 * соответствующего генератора псевдослучайных чисел между вызовами.
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 * @brief Структура состояния для линейного конгруэнтного генератора (LCG).
 */
struct LCG_State {
    unsigned int current_value; ///< Текущее значение генератора (X_n)
};

/**
 * @brief Структура состояния для гибридного регистра сдвига (LFSR).
 */
struct LFSR_State {
    unsigned int lfsr_value; ///< Текущее 32-битное состояние сдвигового регистра
    unsigned int counter;    ///< Счетчик для добавления нелинейности (арифметическое сложение)
};

/**
 * @brief Структура состояния для генератора Xorshift*.
 */
struct Xorshift_State {
    unsigned int state; ///< Текущее 32-битное состояние генератора
};

#endif // STRUCTURES_H