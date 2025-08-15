#include <stdio.h>
#include <ctype.h>
#include <math.h>

//  Для квадратного уравнения
const int MAX_ROOTS = 2;
//  Допустимая погрешность для чисел с плавающей точкой
const double EPS = 0.00000001;

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
    Equation_roots_count r_count;
//  Массив для хранения корней
    double roots[MAX_ROOTS];
} Equation;

//  Главная функция работы с уравнением
void solve_equation(Equation *);
//  Сортирует корни квадратного уравнения
void order_roots(Equation *);
//  Убирает знак нуля (-0.0 -> 0.0)
void normalize_zero(Equation *);

//  Решение линейного уравнения
void solve_linear(Equation *);

//  Поиск дискриминанта
double find_discriminant(Equation *);
//  Решение квадратного уравнения
void solve_quadratic(Equation *);

//  Ввод коэффициентов уравнения
void enter_coefficients(Equation *);
//  Вывод корней квадратного уравнения
void print_roots(Equation *);

//  Сравнение числа с плавающей точкой с нулем
int is_zero(double);
//  Проверяет входной буффер на наличие символов, не являющихся пробельными
int check_input_buffer();
//  Очищает входной буффер
void clear_input_buffer();


int main()
{
    Equation data = {};

    enter_coefficients(&data);
    
    solve_equation(&data);

    print_roots(&data);

    return 0;
}


void solve_equation(Equation * eq)
{
    if (is_zero(eq->a))
        solve_linear(eq);
    else
        solve_quadratic(eq);

    order_roots(eq);
    normalize_zero(eq);
}


void order_roots(Equation * eq)
{
   if (eq->r_count == TWO_ROOTS && eq->roots[0] > eq->roots[1]) {
        double temp = eq->roots[0];

        eq->roots[0] = eq->roots[1];
        eq->roots[1] = temp;
    }
}


void normalize_zero(Equation * eq)
{
    if (is_zero(eq->roots[0]))
        eq->roots[0] = 0.0;

    if (is_zero(eq->roots[1]))
        eq->roots[1] = 0.0;
}


void solve_linear(Equation * eq)
{
    if (is_zero(eq->b) && is_zero(eq->c))
        eq->r_count = INFINITE_ROOTS;
    else if (is_zero(eq->b) && !is_zero(eq->c))
        eq->r_count = NO_ROOTS;
    else {
        eq->r_count = ONE_ROOT;
        eq->roots[0] = -(eq->c / eq->b);
        eq->roots[1] = 0.0;
    }     
}


double find_discriminant(Equation * eq)
{
    return eq->b * eq->b - 4.0 * eq->a * eq->c;
}


void solve_quadratic(Equation * eq) 
{
    double discriminant = find_discriminant(eq);

    if (discriminant > EPS) {
        double root_discriminant = sqrt(discriminant);
        
        eq->r_count = TWO_ROOTS;
        eq->roots[0] = (-eq->b - root_discriminant) / (2.0 * eq->a);
        eq->roots[1] = (-eq->b + root_discriminant) / (2.0 * eq->a);
    } else if (is_zero(discriminant)) {
        eq->r_count = ONE_ROOT;
        eq->roots[0] = (-eq->b) / (2.0 * eq->a);
        eq->roots[1] = 0.0; 
    } else {
        eq->r_count = NO_ROOTS;
        eq->roots[0] = eq->roots[1] = 0.0;
    }
}


void enter_coefficients(Equation * eq)
{
    printf("Enter coefficients\n");

    while (1) {
        if (3 == scanf("%lf%lf%lf", &eq->a, &eq->b, &eq->c) && check_input_buffer())
            break;

        printf("Try again\n");

        clear_input_buffer();
    }
}


void print_roots(Equation * eq)
{
    switch (eq->r_count) {
        case NO_ROOTS: printf("No roots\n"); break;
        case ONE_ROOT: printf("One root: %.3lf\n", eq->roots[0]); break;
        case TWO_ROOTS: printf("Two roots: %.3lf %.3lf\n", eq->roots[0], eq->roots[1]); break;
        case INFINITE_ROOTS: printf("Infinite roots\n"); break;
        default: break;
    }
}


int is_zero(double number)
{
    return fabs(number) <= EPS;
}


int check_input_buffer()
{
    int c = 0;

    while ((c = getchar()) != '\n' && c != EOF)
        if (!isspace(c))
            return 0;

    return 1;
}


void clear_input_buffer()
{
    int c = 0;
    
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
