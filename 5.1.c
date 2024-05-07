#include <stdio.h>
#include <math.h>

// Функція, яка обчислює значення диференціального рівняння
double f(double t, double N, double b, double v) {
    return 1.2 * exp(b * t) + (v / b) * (exp(b * t) - 1);
}

// Метод Рунге-Кутти порядку 4
double runge_kutta(double t, double N, double h, double b, double v) {
    double k1, k2, k3, k4;
    k1 = h * f(t, N, b, v);
    k2 = h * f(t + h/2, N + k1/2, b, v);
    k3 = h * f(t + h/2, N + k2/2, b, v);
    k4 = h * f(t + h, N + k3, b, v);
    return N + (k1 + 2*k2 + 2*k3 + k4) / 6;
}

// Оцінка похибки за правилом Рунге
double runge_error(double y1, double y2, int p) {
    return fabs(y1 - y2) / (pow(2, p) - 1);
}

int main() {
    double b = 0.249988; // коефіцієнт зростання
    double v = 1.250003; // швидкість міграції
    double N0 = 1.2; // початкове значення N(0)
    double t = 0; // початковий час
    double N_exact = 11.853; // точне значення N(4)
    double h1 = 0.1; // перший крок
    double h2 = 0.05; // другий крок

    // Обчислення розв'язку з кроком h1
    double N_approx_h1 = N0;
    while (t < 5) {
        N_approx_h1 = runge_kutta(t, N_approx_h1, h1, b, v);
        printf("h = %.2f: %.6f\n", h1, N_approx_h1);
        t += h1;
    }
    printf("\n");
    // Обчислення розв'язку з кроком h2
    t = 0;
    double N_approx_h2 = N0;
    while (t < 5) {
        N_approx_h2 = runge_kutta(t, N_approx_h2, h2, b, v);
        printf("h = %.2f: %.6f\n", h2, N_approx_h2);
        t += h2;
    }
    printf("\n");
    // Оцінка похибки за правилом Рунге
    double error = runge_error(N_approx_h1, N_approx_h2, 4);

    printf("Наближений розв'язок з кроком h = %.2f: %.6f\n", h1, N_approx_h1);
    printf("Наближений розв'язок з кроком h = %.2f: %.6f\n", h2, N_approx_h2);
    printf("Оцінка похибки за правилом Рунге: %.6f\n", error);

    return 0;
}

