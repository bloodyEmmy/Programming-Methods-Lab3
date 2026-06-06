/**
 * @file generators.h
 * @brief Объявление функций генерации псевдослучайных чисел.
 * @details Содержит три различных алгоритма: LCG со скремблингом, 
 * гибридный LFSR и современный Xorshift*.
 */

#ifndef GENERATORS_H
#define GENERATORS_H

#include "structures.h"

/**
 * @brief Линейный конгруэнтный генератор (LCG) с битовым скремблингом.
 * @param state Ссылка на структуру состояния LCG.
 * @return Псевдослучайное число в диапазоне [0, 9999].
 */
unsigned int my_custom_lcg(LCG_State& state);

/**
 * @brief Гибридный регистр сдвига с линейной обратной связью (LFSR).
 * @details Использует примитивный полином и 32-кратную прокрутку для 
 * устранения зависимости соседних элементов. Смешивает булеву алгебру и арифметику.
 * @param state Ссылка на структуру состояния LFSR.
 * @return Псевдослучайное число в диапазоне [0, 9999].
 */
unsigned int my_hybrid_lfsr(LFSR_State& state);

/**
 * @brief Генератор Xorshift* (модификация со звездочкой).
 * @details Использует битовые сдвиги и умножение на большую константу 
 * для достижения строгого лавинного эффекта.
 * @param state Ссылка на структуру состояния Xorshift.
 * @return Псевдослучайное число в диапазоне [0, 9999].
 */
unsigned int my_xorshift_star(Xorshift_State& state);

#endif // GENERATORS_H