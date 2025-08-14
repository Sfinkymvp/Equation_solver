#include <stdio.h>
#include <math.h>

//  Для квадратного уравнения
#define MAX_ROOTS 2

//  Количество корней уравнения для структуры
typedef enum {
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    INFINITE_ROOTS = -1,
} Equation_roots_count;


typedef struct {
//  Общий вид квадратного уравнения:  ax^2 + bx + c, линейного: bx + c (при а = 0)
    double a, b, c;
//  Количество корней уравнения
    Equation_roots_count rnumber;
//  Массив для хранения корней
    double roots[MAX_ROOTS];
} Equation;

//  Главная функция работы с уравнением
void equation_solution(Equation *);

//  Решение линейного уравнения
void linear_equation(Equation *);

//  Поиск дискриминанта
void find_discriminant(double *, Equation *);
//  Решение квадратного уравнения
void quadratic_equation(Equation *);

//  Ввод коэффициентов уравнения
void enter_coefficients(Equation *);
//  Вывод корней квадратного уравнения
void print_roots(Equation *);


int main()
{
    Equation data = {};

    enter_coefficients(&data);
    
    equation_solution(&data);

    print_roots(&data);

    return 0;
}


void equation_solution(Equation * eq)
{
    if (eq->a == 0 && eq->b == 0) {
        if (eq->c == 0)
            eq->rnumber = INFINITE_ROOTS;
        else 
            eq->rnumber = NO_ROOTS;
    } else if (eq->a == 0) {
        linear_equation(eq);
    } else {
        quadratic_equation(eq);
    }
}


void linear_equation(Equation * eq)
{
    eq->rnumber = ONE_ROOT;
    
    if (eq->c == 0)
        eq->roots[0] = 0;
    else
        eq->roots[0] = -(eq->c / eq->b);
}


void find_discriminant(double * discriminant, Equation * eq)
{
    *discriminant = eq->b * eq->b - (4 * eq->a * eq->c);
}


void quadratic_equation(Equation * eq) 
{
    double discriminant;
    find_discriminant(&discriminant, eq);

    if (discriminant > 0) {
        eq->rnumber = TWO_ROOTS;
        eq->roots[0] = (-eq->b - sqrt(discriminant)) / (2 * eq->a);
        eq->roots[1] = (-eq->b + sqrt(discriminant)) / (2 * eq->a);
    } else if (discriminant == 0) {
        eq->rnumber = ONE_ROOT;
        eq->roots[0] = (-eq->b) / (2 * eq->a);
        eq->roots[1] = 0; 
    } else {
        eq->rnumber = NO_ROOTS;
        eq->roots[0] = eq->roots[1] = 0;
    }
}


void enter_coefficients(Equation * eq)
{
    printf("Enter coefficients\n");

    scanf("%lf%lf%lf", &eq->a, &eq->b, &eq->c);
}


void print_roots(Equation * eq)
{
    switch (eq->rnumber) {
        case NO_ROOTS: printf("No roots\n"); break;
        case ONE_ROOT: printf("One root: %.3lf\n", eq->roots[0]); break;
        case TWO_ROOTS: printf("Two roots: %.3lf %.3lf\n", eq->roots[0], eq->roots[1]); break;
        case INFINITE_ROOTS: printf("Infinite roots\n"); break;
    }
}
