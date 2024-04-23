#include <stdio.h>
#include <math.h>

#define EPSILON 0.00001
#define MAX_ITER 100

double function1(double h, double v) {
    return 1.2 * exp(2 * h) + (v / h) * (exp(2 * h) - 1) - 5.222;
}

double function2(double h, double v) {
    return 1.2 * exp(4 * h) + (v / h) * (exp(4 * h) - 1) - 11.853;
}

double partial_derivative_h1(double h, double v) {
    return 2.4 * exp(2 * h) + (v / h) * (2 * exp(2 * h) - 2) - (v / (h * h)) * (exp(2 * h) - 1);
}

double partial_derivative_v1(double h, double v) {
    return (exp(2 * h) - 1) / h;
}

double partial_derivative_h2(double h, double v) {
    return 4.8 * exp(4 * h) + (v / h) * (4 * exp(4 * h) - 4) - (v / (h * h)) * (exp(4 * h) - 1);
}

double partial_derivative_v2(double h, double v) {
    return (exp(4 * h) - 1) / h;
}

int main() {
    double h = 1.0; // Початкове наближення для h
    double v = 1.0; // Початкове наближення для v

    int iter = 0;
    double error;
    double delta_h, delta_v;

    do {
        // Обчислення значень функцій та похідних
        double F1 = function1(h, v);
        double F2 = function2(h, v);
        double J11 = partial_derivative_h1(h, v);
        double J12 = partial_derivative_v1(h, v);
        double J21 = partial_derivative_h2(h, v);
        double J22 = partial_derivative_v2(h, v);

        // Обчислення оберненого Якобіану
        double determinant = J11 * J22 - J12 * J21;
        double inv_J11 = J22 / determinant;
        double inv_J12 = -J12 / determinant;
        double inv_J21 = -J21 / determinant;
        double inv_J22 = J11 / determinant;

        // Обчислення зміни для h та v
        delta_h = -(inv_J11 * F1 + inv_J12 * F2);
        delta_v = -(inv_J21 * F1 + inv_J22 * F2);

        // Оновлення значень h та v
        h += delta_h;
        v += delta_v;

        // Обчислення похибки
        error = sqrt(delta_h * delta_h + delta_v * delta_v);

        iter++;

        // Перевірка на збіжність
        if (iter > MAX_ITER) {
            printf("Не вдалося знайти розв'язок протягом %d ітерацій.\n", MAX_ITER);
            return 1;
        }

    } while (error > EPSILON);

    printf("Результати: h = %lf, v = %lf\n", h, v);
    printf("Кількість ітерацій: %d\n", iter);
    
    double N_2 = 1.2 * exp(2*h) + (v/h)*(exp(2*h)- 1);
    double N_4 = 1.2 * exp(4*h) + (v/h)*(exp(4*h)- 1);
    printf("Результати: N_2 = %lf, N_4 = %lf\n", N_2, N_4);

    return 0;
}


