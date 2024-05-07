#include <stdio.h>
#include <math.h>

// Задані табличні дані
double x[] = {1, 2, 3, 4, 5, 6, 7, 8};
double y[] = {61.88, 68.1, 71.55, 75.83, 66.9, 73.8, 82.2, 87.98};
int n = sizeof(x) / sizeof(x[0]); // Кількість точок

// 1. Лінійний інтерполяційний сплайн
double linear_interpolation(double x0) {
    for (int i = 1; i < n; i++) {
        if (x0 < x[i]) {
            double t = (x0 - x[i-1]) / (x[i] - x[i-1]);
            return y[i-1] + t * (y[i] - y[i-1]);
        }
    }
    return y[n-1]; // Якщо x0 > останнього значення в таблиці
}

// 2.1. Середнь-квадратичне наближення
void least_squares(double *a, double *b) {
    double sum_x = 0, sum_y = 0, sum_xx = 0, sum_xy = 0;
    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xx += x[i] * x[i];
        sum_xy += x[i] * y[i];
    }
    double denom = n * sum_xx - sum_x * sum_x;
    *a = (n * sum_xy - sum_x * sum_y) / denom;
    *b = (sum_xx * sum_y - sum_x * sum_xy) / denom;
}

// 2.3. Сума квадратів відхилень та максимальна абсолютна похибка
void compute_errors(double a, double b, double *sum_squared_errors, double *max_abs_error) {
    *sum_squared_errors = 0;
    *max_abs_error = 0;
    for (int i = 0; i < n; i++) {
        double error = y[i] - (a * x[i] + b);
        *sum_squared_errors += error * error;
        if (fabs(error) > *max_abs_error) {
            *max_abs_error = fabs(error);
        }
    }
}

int main() {
    // 1. Лінійний інтерполяційний сплайн
    double x_interpolate = 3.5; // Невузлова точка для інтерполяції
    double interpolated_value = linear_interpolation(x_interpolate);
    printf("Значення у точці %.2f за лінійним інтерполяційним сплайном: %.2f\n", x_interpolate, interpolated_value);

    // 2. Середнь-квадратичне наближення
    double a, b;
    least_squares(&a, &b);
    printf("Функція phi(x) = %.2f * x + %.2f\n", a, b);

    // 2.3. Обчислення суми квадратів відхилень та максимальної абсолютної похибки
    double sum_squared_errors, max_abs_error;
    compute_errors(a, b, &sum_squared_errors, &max_abs_error);
    printf("Сума квадратів відхилень: %.2f\n", sum_squared_errors);
    printf("Максимальна абсолютна похибка: %.2f\n", max_abs_error);

    return 0;
}
