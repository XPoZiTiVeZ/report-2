#include <math.h>
#include <stddef.h>
#include "methods.h"

double root(double (*f)(double), double (*g)(double), double a, double b, double eps1) {
    static int internal_iterations = 0;
    
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
        
        if (Fa * Fc <= 0) {
            b = c;
        } else {
            a = c;
        }
    }
    
    return (a + b) / 2.0;
}

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
        
    } while (n <= 4 || fabs(I_2n - I_n) / 15.0 >= eps2);
    
    return I_2n;
}