#include <stdio.h>
#include <math.h>

double f(double t, double r) {
    return sqrt(pow(r - r * cos(t), 2) + pow(r * sin(t), 2));
}

double simpsons_rule(double a, double b, int n, double r) {
    double h = (b - a) / n;
    double sum = f(a, r) + f(b, r);

    for (int i = 1; i < n; i += 2) {
        sum += 4 * f(a + i * h, r);
    }
    for (int i = 2; i < n - 1; i += 2) {
        sum += 2 * f(a + i * h, r);
    }

    return (h / 3) * sum;
}

int main() {
    double r = 1.0; // Радіус круга
    double a = 0.0; // Початкове значення параметра t
    double b = M_PI; // Кінцеве значення параметра t
    int steps1 = 100; // Кількість кроків для першого обчислення
    int steps2 = 1000; // Кількість кроків для другого обчислення

    double integral1 = simpsons_rule(a, b, steps1, r);
    double integral2 = simpsons_rule(a, b, steps2, r);

    printf("Довжина циклоїди з кроком 0.01: %.6f\n", integral1);
    printf("Довжина циклоїди з кроком 0.001: %.6f\n", integral2);

    return 0;
}

