#include <math.h>
#include <stddef.h>
#include "methods.h"

/* 
    Статическая переменная для хранения числа итераций последнего вызова функции root.
    Используется для того, чтобы вернуть число итераций без изменения сигнатуры функции,
    так как по заданию сигнатура строго фиксирована: root(f, g, a, b, eps).
*/
static int internal_iterations = 0;


/*
    Функция вычисления корня уравнения f(x) = g(x) на отрезке [a, b] с точностью eps1.
    Используется метод деления отрезка пополам (дихотомии).
    Если передать f == NULL, функция вернет число итераций, затраченных при предыдущем вызове.
*/
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1) {
    if (f == NULL) {
        return (double)internal_iterations;
    }
    
    double c;
    internal_iterations = 0;
    
    while ((b - a) > eps1) {
        internal_iterations++;
        c = (a + b) / 2.0;
        
        double Fa = f(a) - g(a);
        double Fc = f(c) - g(c);
        
        // Если функция меняет знак на левой половине отрезка
        if (Fa * Fc <= 0) {
            b = c;
        } else {
            a = c;
        }
    }
    
    return (a + b) / 2.0;
}

/*
    Функция вычисления определенного интеграла от функции f на отрезке [a, b] с точностью eps2.
    Используется квадратурная формула Симпсона (парабол) с правилом Рунге для оценки погрешности.
*/
double integral(double (*f)(double), double a, double b, double eps2) {
    int n = 2;
    double I_n = 0.0;
    double I_2n = 0.0;
    
    do {
        I_n = I_2n;
        n *= 2;
        double h = (b - a) / n;
        double sum = f(a) + f(b);
        
        for (int i = 1; i < n; i++) {
            double x = a + i * h;
            if (i % 2 == 0) {
                sum += 2 * f(x);
            } else {
                sum += 4 * f(x);
            }
        }
        I_2n = sum * h / 3.0;

        // Погрешность для метода Симпсона оценивается делением на 15 (правило Рунге, p=4)
    } while (n <= 4 || fabs(I_2n - I_n) / 15.0 >= eps2);
    
    return I_2n;
}