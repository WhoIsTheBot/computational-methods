import numpy as np
import matplotlib.pyplot as plt

# Функція, яка обчислює значення диференціального рівняння
def f(t, N, b, v):
    return 1.2 * np.exp(b * t) + (v / b) * (np.exp(b * t) - 1)

# Метод Рунге-Кутта порядку 4
def runge_kutta(t, N, h, b, v):
    k1 = h * f(t, N, b, v)
    k2 = h * f(t + h/2, N + k1/2, b, v)
    k3 = h * f(t + h/2, N + k2/2, b, v)
    k4 = h * f(t + h, N + k3, b, v)
    return N + (k1 + 2*k2 + 2*k3 + k4) / 6

# Оцінка похибки за правилом Рунге
def runge_error(y1, y2, p):
    return np.abs(y1 - y2) / (2**p - 1)

b = 0.249988  # коефіцієнт зростання
v = 1.250003  # швидкість міграції
N0 = 1.2      # початкове значення N(0)
t_max = 5     # максимальний час

h1 = 0.1      # перший крок
h2 = 0.05     # другий крок

# Обчислення розв'язку з кроком h1
t_values_h1 = np.arange(0, t_max + h1, h1)
N_values_h1 = np.zeros_like(t_values_h1)
N_values_h1[0] = N0
for i in range(1, len(t_values_h1)):
    N_values_h1[i] = runge_kutta(t_values_h1[i-1], N_values_h1[i-1], h1, b, v)
    print(N_values_h1[i])

# Обчислення розв'язку з кроком h2
t_values_h2 = np.arange(0, t_max + h2, h2)
N_values_h2 = np.zeros_like(t_values_h2)
N_values_h2[0] = N0
for i in range(1, len(t_values_h2)):
    N_values_h2[i] = runge_kutta(t_values_h2[i-1], N_values_h2[i-1], h2, b, v)
    print(N_values_h2[i])

# Визначення спільної області значень t
t_values_common = np.arange(0, t_max + min(h1, h2), min(h1, h2))

# Візуалізація графіків
plt.figure(figsize=(10, 6))
plt.plot(t_values_common[:len(N_values_h1)], N_values_h1, label=f'h = {h1}', color="red")
plt.plot(t_values_common[:len(N_values_h2)], N_values_h2, label=f'h = {h2}', color="green")

plt.title("Розв'язок диференціального рівняння")
plt.xlabel('Час')
plt.ylabel('N(t)')
plt.legend()
plt.grid(True)
plt.show()

# Оцінка похибки за правилом Рунге
error = runge_error(N_values_h1[-1], N_values_h2[-1], 4)
print(f"Оцінка похибки за правилом Рунге: {error}")
