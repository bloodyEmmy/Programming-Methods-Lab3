import matplotlib.pyplot as plt
import csv

sizes = []
time_lcg = []
time_lfsr = []
time_xorshift = []
time_std = []

with open('benchmark.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)
    for row in reader:
        sizes.append(int(row[0]))
        time_lcg.append(int(row[1]))
        time_lfsr.append(int(row[2]))
        time_xorshift.append(int(row[3]))
        time_std.append(int(row[4]))

plt.figure(figsize=(10, 6))

plt.plot(sizes, time_lcg, label='Метод 1: LCG', marker='o', linewidth=2)
plt.plot(sizes, time_lfsr, label='Метод 2: Гибридный LFSR', marker='o', linewidth=2)
plt.plot(sizes, time_xorshift, label='Метод 3: Xorshift*', marker='o', linewidth=2)
plt.plot(sizes, time_std, label='Стандартный C++ rand()', marker='s', linewidth=2, linestyle='--')

plt.title('Сравнение скорости генерации ПСЧ (Логарифмический масштаб)', fontsize=14)
plt.xlabel('Количество генерируемых элементов (log)', fontsize=12)
plt.ylabel('Время выполнения в микросекундах (log)', fontsize=12)

plt.xscale('log')
plt.yscale('log')

plt.grid(True, which="both", ls="-", alpha=0.2)
plt.grid(True, which="major", ls="-", alpha=0.6)

plt.legend()

plt.savefig('benchmark_plot_log.png', dpi=300, bbox_inches='tight')
plt.show()