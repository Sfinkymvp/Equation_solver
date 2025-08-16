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
//  Вывод корней уравнения
void print_roots(Equation *);
//  Вывод корней уравнения в красивом виде
void print_equation(Equation *);

//  Сравнение числа с плавающей точкой с нулем
int is_zero(double);
//  Проверяет входной буффер на наличие символов, не являющихся пробельными
int check_input_buffer();
//  Очищает входной буффер
void clear_input_buffer();

//  Выводит приветствие с котиком
void print_hello();
//  Выводит сообщение о тождественно ложном уравнении
void print_no_roots(Equation *);
//  Выводит сообщение о наличии одного корня
void print_one_root(Equation *);
//  Выводит сообщение о наличии двух корней
void print_two_roots(Equation *);
//  Выводит сообщение о тождестве
void print_infinite_roots();


int main()
{
    Equation data = {};
    
    print_hello();

    enter_coefficients(&data);
    
    solve_equation(&data);

    print_equation(&data);

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


void print_equation(Equation * eq)
{   
    switch (eq->r_count) {
        case NO_ROOTS: print_no_roots(eq); break;
        case ONE_ROOT: print_one_root(eq); break;
        case TWO_ROOTS: print_two_roots(eq); break;
        case INFINITE_ROOTS: print_infinite_roots(); break;
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


void print_hello() 
{
    printf("   A_A                                              \n"
           "  (-.-)             _   _        _ _          _     \n"
           "   |-|             | | | |      | | |        | |    \n"
           "  /   \\            | |_| | ___  | | |  ___   | |   \n"
           " |     |  __       |  _  |/ _ \\ | | | / _ \\  |_|  \n"
           " |  || | |  \\___   | | | |  __/ | | || (_) |  _    \n"
           " \\_||_/_/          \\_| |_/\\___| |_|_| \\___/  |_|\n");

}

void print_no_roots(Equation * eq)
{
    if (is_zero(eq->a))
        printf("%.2lf = 0 is not identical, no roots\n", eq->c);
    else
        printf("%.2lfx^2%+.2lfx%+.2lf = 0 has a negative discriminant, no roots\n",
                eq->a, eq->b, eq->c); 
}


void print_one_root(Equation * eq)
{
    if (is_zero(eq->a))
        printf("%.2lfx%+.2lf = 0 has one root:\n"
               "x = %.3lf\n", eq->b, eq->c, eq->roots[0]);
    else
        printf("%.2lfx^2%+.2lfx%+.2lf = 0 has one root:\n"
               "x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0]);
}


void print_two_roots(Equation * eq)
{
    printf("%.2lfx^2%+.2lfx%+.2lf = 0 has two roots:\n"
           "x = %.3lf, x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0], eq->roots[1]);
}


void print_infinite_roots()
{
    printf("0 = 0 is an identity, infinite roots\n");
}


