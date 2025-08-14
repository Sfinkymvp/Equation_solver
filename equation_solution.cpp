#include <stdio.h>
#include <math.h>


typedef struct {
    double a, b, c;  //  Общий вид уравнения:  ax^2 + bx + c
    double d;  //  d = b^2 - 4ac
    double x1, x2;  //  При отсутствии корня в переменную записывается 0
} Equation;


//  Проверка типа уравнения
int equation_check(Equation *);
//  Решение квадратного уравнения
void quadratic_equation(Equation *);
//  Поиск дискриминанта
void finding_discriminant(Equation *);
//  Поиск корней квадратного уравнения
void roots(Equation *);
//  Ввод коэффициентов уравнения
void entering_coefficients(Equation *);
//  Вывод корней квадратного уравнения
void print_roots(Equation *);


int main()
{
    Equation data;

    entering_coefficients(&data);
    
    if (equation_check(&data)) {
        quadratic_equation(&data);
    
        print_roots(&data);
    }

    return 0;
}


int equation_check(Equation * eq)
{
    if (eq->a == 0) { 
        printf("The equation is not quadratic!\n");
        
        if (eq->b != 0) {
            printf("One root:\n");
            printf("%.3lf\n", -(eq->c / eq->b));
        } else if (eq->c == 0) {
            printf("Infinity of roots\n");
        } else {
            printf("No roots\n");
        }
    
        return 0;
    }

    return 1;
}


void quadratic_equation(Equation * eq)
{
    finding_discriminant(eq);

    roots(eq);
}


void finding_discriminant(Equation * eq)
{
    eq->d = eq->b * eq->b - (4 * eq->a * eq->c);
}


void roots(Equation * eq) 
{
    if (eq->d > 0) {
        eq->x1 = (-eq->b - sqrt(eq->d)) / (2 * eq->a);
        eq->x2 = (-eq->b + sqrt(eq->d)) / (2 * eq->a);
    } else if (eq->d == 0) {
        eq->x1 = (-eq->b) / (2 * eq->a);
        eq->x2 = 0;
    } else {
        eq->x1 = eq->x2 = 0;
    }
}


void entering_coefficients(Equation * eq)
{
    printf("Enter coefficients\n");

    scanf("%lf%lf%lf", &eq->a, &eq->b, &eq->c);
}


void print_roots(Equation * eq)
{
    if (eq->d > 0) {
        printf("Two roots:\n");
        printf("%.3lf %.3lf\n", eq->x1, eq->x2);
    } else if (eq->d == 0) {
        printf("One root:\n");
        printf("%.3lf\n", eq->x1);
    } else {
        printf("no roots\n");
    }
}
