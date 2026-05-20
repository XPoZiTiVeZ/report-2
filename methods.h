#ifndef METHODS_H
#define METHODS_H

// Функция вычисления корня уравнения f(x) = g(x) на отрезке [a, b].
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1);

// Функция вычисления определенного интеграла от функции f(x) на отрезке [a, b]
double integral(double (*f)(double), double a, double b, double eps2);

/*
double root(double (*f)(double), 
            double (*g)(double), 
            double (*f_der)(double), 
            double (*g_der)(double), 
            double a, 
            double b, 
            double eps1);
*/

#endif