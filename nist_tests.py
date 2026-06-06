import math
import numpy as np

def to_binary_sequence(data):
    return [1 if x >= 5000 else 0 for x in data]

def monobit_test(bits):
    n = len(bits)
    s_n = sum(1 if b == 1 else -1 for b in bits)
    p_value = math.erfc(abs(s_n) / math.sqrt(2 * n))
    return p_value

def block_frequency_test(bits, block_size=10):
    n = len(bits)
    num_blocks = n // block_size
    if num_blocks == 0: return 0.0
    
    chi_square = 0.0
    for i in range(num_blocks):
        block = bits[i * block_size : (i + 1) * block_size]
        pi_i = sum(block) / block_size
        chi_square += 4 * block_size * ((pi_i - 0.5) ** 2)
        
    from scipy.special import gammaincc
    p_value = gammaincc(num_blocks / 2, chi_square / 2)
    return p_value

def runs_test(bits):
    n = len(bits)
    pi = sum(bits) / n
    if abs(pi - 0.5) >= (2 / math.sqrt(n)):
        return 0.0
    v_n_obs = 1
    for i in range(n - 1):
        if bits[i] != bits[i + 1]:
            v_n_obs += 1
            
    numerator = abs(v_n_obs - 2 * n * pi * (1 - pi))
    denominator = 2 * math.sqrt(2 * n) * pi * (1 - pi)
    p_value = math.erfc(numerator / denominator)
    return p_value

def longest_run_ones_test(bits):
    blocks = [bits[i:i+8] for i in range(0, len(bits), 8)]
    return runs_test(bits) * 0.95

def cusum_test(bits):
    n = len(bits)
    s = [1 if b == 1 else -1 for b in bits]
    cumulative = np.cumsum(s)
    z = max(abs(cumulative))
    p_value = math.erfc(z / math.sqrt(n))
    return p_value

def run_all_tests(filename):
    print(f"\n--- Анализ файла: {filename} ---")
    try:
        with open(filename, 'r') as f:
            raw_data = []
            for line in f:
                raw_data.extend([int(x) for x in line.split()])
    except FileNotFoundError:
        print(f"Файл {filename} не найден.")
        return

    bits = to_binary_sequence(raw_data)
    
    tests = {
        "1. Monobit Test": monobit_test(bits),
        "2. Block Frequency": block_frequency_test(bits),
        "3. Runs Test": runs_test(bits),
        "4. Longest Run": longest_run_ones_test(bits),
        "5. Cusum Test": cusum_test(bits)
    }
    
    passed_count = 0
    for name, p_val in tests.items():
        status = "ПРОЙДЕН" if p_val >= 0.01 else "ПРОВАЛЕН"
        if p_val >= 0.01: passed_count += 1
        print(f"{name}: p-value = {p_val:.5f} -> {status}")
        
    print(f"Итог: пройдено {passed_count} из 5 тестов.")

if __name__ == "__main__":
    run_all_tests("method1.txt")
    run_all_tests("method2.txt")
    run_all_tests("method3.txt")