import matplotlib.pyplot as plt
import csv

sizes = []
time_lcg = []
time_lfsr = []
time_xorshift = []
time_std = []

# Читаем данные из нашего C++ бенчмарка
with open('benchmark.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader) # Пропускаем строку с заголовками
    for row in reader:
        sizes.append(int(row[0]))
        time_lcg.append(int(row[1]))
        time_lfsr.append(int(row[2]))
        time_xorshift.append(int(row[3]))
        time_std.append(int(row[4]))

# Настраиваем полотно графика
plt.figure(figsize=(10, 6))

# Рисуем 4 линии
plt.plot(sizes, time_lcg, label='Метод 1: LCG', marker='o', linewidth=2)
plt.plot(sizes, time_lfsr, label='Метод 2: Гибридный LFSR', marker='o', linewidth=2)
plt.plot(sizes, time_xorshift, label='Метод 3: Xorshift*', marker='o', linewidth=2)
plt.plot(sizes, time_std, label='Стандартный C++ rand()', marker='s', linewidth=2, linestyle='--')

# Оформляем график
plt.title('Сравнение скорости генерации ПСЧ (Логарифмический масштаб)', fontsize=14)
plt.xlabel('Количество генерируемых элементов (log)', fontsize=12)
plt.ylabel('Время выполнения в микросекундах (log)', fontsize=12)

# Включаем логарифмический масштаб для ОБЕИХ осей
plt.xscale('log')
plt.yscale('log')

# Настраиваем сетку так, чтобы она отображала промежуточные логарифмические линии
plt.grid(True, which="both", ls="-", alpha=0.2)
plt.grid(True, which="major", ls="-", alpha=0.6)

# Добавляем легенду
plt.legend()

# Сохраняем график в картинку
plt.savefig('benchmark_plot_log.png', dpi=300, bbox_inches='tight')
plt.show()