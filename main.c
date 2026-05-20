#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methods.h"
#include "functions.h"

// Точность вычисления корней
const double EPS1 = 0.001;
// Точность вычисления интегралов
const double EPS2 = 0.0001;


/*
    Функция выбора математических функций по номеру
*/
double (*get_func_by_id(int id))(double) {
    if (id == 1) return f1;
    if (id == 2) return f2;
    if (id == 3) return f3;
    return NULL;
}

/*
    Вывод меню подсказки
*/
void print_hint(void) {
    printf("Использование: ./program [<аргументы>]\n");
    printf("Опции:\n");
    printf("  -h, --help       Показать эту справку\n");
    printf("  -r, --roots      Вывести абсциссы точек пересечения\n");
    printf("  -i, --iters      Вывести число итераций метода поиска корней\n");
    printf("  -t, --test root <f_id> <g_id> <a> <b> <eps>\n");
    printf("                   Тестирование функции root\n");
    printf("  -t, --test int <f_id> <a> <b> <eps>\n");
    printf("                   Тестирование функции integral\n");
}

/*
    Тестирование функции нахождения пересечения данных функций на введённом интервале поиска
*/
void test_func(int i, int argc, char *argv[]) {
    int f_id = atoi(argv[i+2]);
    int g_id = atoi(argv[i+3]);
    double ta = atof(argv[i+4]);
    double tb = atof(argv[i+5]);
    double teps = atof(argv[i+6]);
    
    double res = root(get_func_by_id(f_id), get_func_by_id(g_id), ta, tb, teps);
    printf("Test root: %lf\n", res);
}

/*
    Тестирование вычисления интеграла функции с собственным интервалом
*/
void test_int(int i, int argc, char *argv[]) {
    int f_id = atoi(argv[i+2]);
    double ta = atof(argv[i+3]);
    double tb = atof(argv[i+4]);
    double teps = atof(argv[i+5]);
    
    double res = integral(get_func_by_id(f_id), ta, tb, teps);
    printf("Test integral: %lf\n", res);
}

int main(int argc, char *argv[]) {
    int print_roots = 0;
    int print_iters = 0;
    
    for (int i = 1; i < argc; i++) { // Сканирование переданных аргументов
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_hint();
            return 0;
        } 
        else if (strcmp(argv[i], "--roots") == 0 || strcmp(argv[i], "-r") == 0) {
            print_roots = 1;
        } 
        else if (strcmp(argv[i], "--iters") == 0 || strcmp(argv[i], "-i") == 0) {
            print_iters = 1;
        }
        else if (strcmp(argv[i], "--test") == 0 || strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc && strcmp(argv[i+1], "root") == 0 && i + 6 < argc) {
                test_func(i, argc, argv);
                return 0;
            }
            else if (i + 1 < argc && strcmp(argv[i+1], "int") == 0 && i + 5 < argc) {
                test_int(i, argc, argv);
                return 0; 
            } else {
                printf("Ошибка: неверные аргументы.\n");
                return 1;
            }
        }
    } 

    // Поочерёдное вычисление пересечений между каждой парой функций
    double x1 = root(f1, f3, -5.0, -3.0, EPS1);
    int iters1 = (int)root(NULL, NULL, 0, 0, 0);

    double x2 = root(f3, f2, -2.5, -0.5, EPS1);
    int iters2 = (int)root(NULL, NULL, 0, 0, 0);

    double x3 = root(f1, f2, -1.0, -0.1, EPS1);
    int iters3 = (int)root(NULL, NULL, 0, 0, 0);

    // Отладочная печать абсцисс точек пересечения при флаге
    if (print_roots) {
        printf("Точки пересечения:\n");
        printf("  f1 и f3: %lf\n", x1);
        printf("  f3 и f2: %lf\n", x2);
        printf("  f1 и f2: %lf\n", x3);
    }

    // Отладочная печать количества итераций для вычисления результата с нужной точностью
    if (print_iters) {
        printf("Число итераций (root):\n");
        printf("  Для x1: %d\n", iters1);
        printf("  Для x2: %d\n", iters2);
        printf("  Для x3: %d\n", iters3);
    }

    // Вычисление площадей по отдельности
    double int_top = integral(f1, x1, x3, EPS2);
    double int_bl = integral(f3, x1, x2, EPS2);
    double int_br = integral(f2, x2, x3, EPS2);

    // Вычисление итоговой площади ограниченной данными фукнциями
    double area = int_top - (int_bl + int_br);

    printf("Площадь фигуры: %lf\n", area);

    return 0;
}