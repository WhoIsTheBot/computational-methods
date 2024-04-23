public class Main {
    
    // Обчислює похідну x по відношенню до параметра t для заданого радіусу r
    public static double dxdt(double t, double r) {
        return r - r * Math.cos(t);
    }
    
    // Обчислює похідну y по відношенню до параметра t для заданого радіусу r
    public static double dydt(double t, double r) {
        return r * Math.sin(t);
    }
    
    // Обчислює значення інтегранда (довжини елементарного відрізка дуги) 
    // для заданих значень параметра t і радіусу r
    public static double lengthIntegrand(double t, double r) {
        double dx = dxdt(t, r);
        double dy = dydt(t, r);
        return Math.sqrt(dx * dx + dy * dy);
    }
    
    // Обчислює наближений інтеграл методом складеної квадратурної формули Сімпсона
    // для заданої функції інтегранда f на відрізку [a, b] з кількістю кроків steps
    // для заданого радіусу r
    public static double integrate(IntegrandFunction f, double a, double b, int steps, double r) {
        double h = (b - a) / steps;
        double sum = f.apply(a, r) + f.apply(b, r); // Початкове значення суми
        
        // Додавання значень інтегранда на парних та непарних кроках
        for (int i = 1; i < steps; i++) {
            double x = a + i * h;
            sum += 2 * f.apply(x, r) * (i % 2 == 0 ? 2 : 4);
        }
        
        return sum * h / 3; // Повертає наближене значення інтегралу
    }
    
    public static void main(String[] args) {
        double r = 1.0; // Радіус циклоїди
        
        double a = 0; // Початкове значення параметру t
        double b = 2 * Math.PI; // Кінцеве значення параметру t
        int steps = 10000; // Кількість кроків для апроксимації інтегралу
        
        // Обчислення довжини арки циклоїди методом інтегрування
        double length = integrate(Main::lengthIntegrand, a, b, steps, r);
        System.out.println("Довжина арки циклоїди: " + length);
    }
}

// Інтерфейс, що описує функціональний контракт для інтегранда
interface IntegrandFunction {
    double apply(double t, double r); // Метод для обчислення значення інтегранда
}



