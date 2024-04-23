import numpy as np
import matplotlib.pyplot as plt

# Таблиці значень
x_values = np.array([1, 2, 3, 4, 5, 6, 7, 8])
y_values = np.array([61.88, 68.1, 71.55, 75.83, 66.9, 73.8, 82.2, 87.98])

# Функція для побудови лінійного інтерполяційного сплайну
def linear_spline(x, x_values, y_values):
    n = len(x_values)
    for i in range(n-1):
        if x_values[i] <= x <= x_values[i+1]:
            return ((x - x_values[i+1]) * y_values[i] + (x_values[i] - x) * y_values[i+1]) / (x_values[i] - x_values[i+1])

# Функція для середньоквадратичного наближення
def least_squares(x, x_values, y_values):
    n = len(x_values)
    A = np.vstack([np.ones(n), x_values]).T
    a, b = np.linalg.lstsq(A, y_values, rcond=None)[0]
    return a + b * x

# Визначення точок для візуалізації
x_range = np.linspace(min(x_values), max(x_values), 100)
y_linear_spline = [linear_spline(x, x_values, y_values) for x in x_range]
y_least_squares = [least_squares(x, x_values, y_values) for x in x_range]

# Задана невузлова точка для інтерполяції
x_new = 4.5
# Інтерполяція значення функції в невузловій точці
y_interpolated = linear_spline(x_new, x_values, y_values)
print(f"Інтерпольоване значення функції в точці {x_new}: {y_interpolated}")

# Візуалізація результатів
plt.figure(figsize=(10, 6))
plt.scatter(x_values, y_values, color='red', label='Таблиця значень')
plt.plot(x_range, y_linear_spline, label='Лінійний інтерполяційний сплайн', linestyle='--')
plt.plot(x_range, y_least_squares, label='Середньоквадратичне наближення')
plt.title('Побудова сплайну та наближення')
plt.xlabel('Семестр')
plt.ylabel('Середній бал')
plt.legend()
plt.grid(True)
plt.show()
