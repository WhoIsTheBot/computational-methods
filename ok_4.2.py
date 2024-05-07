import numpy as np
import matplotlib.pyplot as plt

# Задані табличні дані
x = np.array([1, 2, 3, 4, 5, 6, 7, 8])
y = np.array([61.88, 68.1, 71.55, 75.83, 66.9, 73.8, 82.2, 87.98])

# 1. Лінійний інтерполяційний сплайн
def linear_interpolation(x0):
    for i in range(1, len(x)):
        if x0 < x[i]:
            t = (x0 - x[i-1]) / (x[i] - x[i-1])
            return y[i-1] + t * (y[i] - y[i-1])
    return y[-1]  # Якщо x0 > останнього значення в таблиці

# 2.1. Середньоквадратичне наближення
a, b = np.polyfit(x, y, 1)
print(f"Функція phi(x) = {a:.2f} * x + {b:.2f}")

# Візуалізація
plt.scatter(x, y, label="Табличні дані")
x_interp = np.linspace(min(x), max(x), 100)
y_interp = [linear_interpolation(xi) for xi in x_interp]
plt.plot(x_interp, y_interp, label="Лінійний інтерполяційний сплайн", color='red')

# Візуалізація середньоквадратичного наближення
y_approx = a * x + b
plt.plot(x, y_approx, label="Середньоквадратичне наближення", color='green')

plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.grid(True)
plt.show()

