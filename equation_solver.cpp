#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//  Для квадратного уравнения
const int MAX_ROOTS = 2;
//  Допустимая погрешность для чисел с плавающей точкой
const double EPS = 0.00000001;
//  Допустимая длина имени файла
const int MAX_BUFFER_LEN = 100;

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

//  Тело программы
void launch_solver();
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

//  Выбор способа получения коэффициентов
bool get_coefficients(Equation *);
//  Ввод пунктов меню
int select_input_mode();
//  Ввод коэффициентов уравнения
void enter_coefficients(Equation *);
//  Чтение коэффициентов уравнения из файла
bool import_coefficients(Equation *);

//  Выводит результат ответа пользователя (Да/Нет)
bool check_agreement();
//  Переносит решение уравнения в файл 
void transfer_equation(Equation *);
//  Производит запись решения уравнения в файл
void export_equation(Equation *, char *, const char *);

//  Вывод корней уравнения
void print_equation(Equation *, FILE * out);

//  Сравнивание числа с плавающей точкой с нулем
bool is_zero(double);
//  Проверяет входной буффер на наличие символов, не являющихся пробельными
bool check_input_buffer(FILE *);
//  Проверяет доступность файла для чтения
bool is_file_exists(char *);
//  Очищает входной буффер
void clear_input_buffer();
//  Очищает терминал
void clear_screen();

//  Выводит приветствие с котиком
void print_hello();
//  Выводит прощание
void print_byebye();

//  Выводит сообщение о тождественно ложном уравнении
void print_no_roots(Equation *, FILE *);
//  Выводит сообщение о наличии одного корня
void print_one_root(Equation *, FILE *);
//  Выводит сообщение о наличии двух корней
void print_two_roots(Equation *, FILE *);
//  Выводит сообщение о тождестве
void print_infinite_roots(FILE *);


int main()
{
    launch_solver();

    return 0;
}


void launch_solver()
{
    Equation eq = {};

    clear_screen();
    print_hello();
    
    while (true) {
        bool status = get_coefficients(&eq);
        
        if (status == false)
            break;
        
        solve_equation(&eq);

        print_equation(&eq, stdout);

        transfer_equation(&eq);
    }
 
    print_byebye(); 
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


bool get_coefficients(Equation * eq)
{
    printf("\nSelect the coefficient input mode:\n"
           "1 - Keyboard input\n"
           "2 - Reading from file\n"
           "3 - Quit\n\n");

    while (true) {
        switch (select_input_mode()) {
            case '1': {
                clear_screen();
                enter_coefficients(eq);
                return true;
            }
            case '2': {
                clear_screen();
                if (import_coefficients(eq))
                    return true;

                printf("Select the coefficient input mode again:\n"
                       "(1 - Keyboard / 2 - File / 3 - Quit)\n");
                break;
            }
            case '3': return false; 
        }
    } 
}


int select_input_mode()
{
    int answer = 0;
    
    while (true) {
        answer = getchar();

        if ('1' <= answer && answer <= '3' && check_input_buffer(stdin))
            return answer;

        printf("Try again\n");

        clear_input_buffer();
    }
}


void enter_coefficients(Equation * eq)
{
    printf("Enter coefficients\n");

    while (true) {
        if (3 == scanf("%lf%lf%lf", &eq->a, &eq->b, &eq->c) && check_input_buffer(stdin))
            break;

        printf("Try again\n");

        clear_input_buffer();
    }
}


void enter_answer(char * answer)
{
    fgets(answer, MAX_BUFFER_LEN, stdin);
    
    int len = strlen(answer);
//  Проверка длины имени файла
    if (len > 0 && answer[len - 1] == '\n') {
        answer[len - 1] = '\0';
    } else {
//  Очистка всего в случае неудачного чтения
        answer[0] = '\0';
        clear_input_buffer();
    }
}


bool import_coefficients(Equation * eq)
{
    printf("Enter file name:\n");
    
    char file_name[MAX_BUFFER_LEN] = {};

    enter_answer(file_name);

    if (file_name[0] == '\0') {
        printf("\nFile name too long\n");
        return false;
    }

//  Проверка возможности доступа к файлу        
    if (is_file_exists(file_name)) {
        FILE * in = fopen(file_name, "r"); 
//  Проверка возможности чтения коэффициентов
        if (3 == fscanf(in, "%lf%lf%lf", &eq->a, &eq->b, &eq->c) && check_input_buffer(in)) {
            printf("\nImport successful\n");
            return true;
        } else {
            printf("\nFailed to read coefficients from file '%s'\n", file_name);
        }

        fclose(in);
    } else {
        printf("\nFailed to open file '%s'\n", file_name);
    }

    return false; 
}


bool check_agreement()
{
    const char * agreements[] = {"yes", "y", "ok", "okay", "1",
                                 "da", "true", "да", "окей", "ок"};
    const int len_agreements = sizeof(agreements) / sizeof(*agreements);    

    char answer[MAX_BUFFER_LEN] = {};
    
    enter_answer(answer);

    if (answer[0] == '\0')
        return false;

    for (int index = 0; index < len_agreements; index++)
        if (0 == strcasecmp(answer, agreements[index]))
            return true;

    return false;  
}


void transfer_equation(Equation * eq)
{
    printf("\nDo you want to write the solution to a file? (y/n)\n");

    if (!check_agreement())
        return;

    printf("Enter file name:\n");

    char file_name[MAX_BUFFER_LEN] = {};

    enter_answer(file_name);

    if (file_name[0] == '\0') {
        printf("\nFile name too long\n");
        return;
    }

    if (!is_file_exists(file_name)) {
        export_equation(eq, file_name, "w");
        printf("\nThe solution has been successfully written to the file.\n");
    } else {
        printf("\nA file with this name already exists,\n"
               "do you want to overwrite it? (y/n)\n");

        if (check_agreement()) {
            export_equation(eq, file_name, "w");
            printf("\nThe solution has been successfully written to the file.\n");
        }
    }  
}


void export_equation(Equation * eq, char * file_name, const char * mode)
{
    FILE * out = fopen(file_name, mode);

    print_equation(eq, out);

    fclose(out);
}


void print_equation(Equation * eq, FILE * out)
{   
    switch (eq->r_count) {
        case NO_ROOTS: print_no_roots(eq, out); break;
        case ONE_ROOT: print_one_root(eq, out); break;
        case TWO_ROOTS: print_two_roots(eq, out); break;
        case INFINITE_ROOTS: print_infinite_roots(out); break;
        default: fprintf(out, "ERROR: enum parameter not processed\n"); break;
    }

}


bool is_zero(double number)
{
    return fabs(number) <= EPS;
}


bool check_input_buffer(FILE * in)
{
    int c = 0;

    while ((c = getc(in)) != '\n' && c != EOF)
        if (!isspace(c))
            return false;

    return true;
}


bool is_file_exists(char * file_name)
{
    FILE * in = fopen(file_name, "r");
    
    if (!in)
        return false;

    fclose(in);
    
    return true;
}


void clear_input_buffer()
{
    int c = 0;
    
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}


void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
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


void print_byebye()
{
    printf(" _                  _                  _     \n"
           "| |                | |                | |    \n"
           "| |__  _   _  ___  | |__  _   _  ___  | |    \n"
           "| '_ \\| | | |/ _ \\ | '_ \\| | | |/ _ \\ |_|\n"
           "| |_) | |_| |  __/ | |_) | |_| |  __/  _     \n"
           "|_.__/ \\__, |\\___| |_.__/ \\__, |\\___| |_|\n"
           "        __/ |              __/ |             \n"
           "       |___/              |___/              \n");
            
}


void print_no_roots(Equation * eq, FILE * out)
{
    if (is_zero(eq->a))
        printf("\n%.2lf = 0 is not identical, no roots\n\n", eq->c);
    else
        printf("\n%.2lfx^2%+.2lfx%+.2lf = 0 has a negative discriminant, no roots\n\n",
                eq->a, eq->b, eq->c); 
}


void print_one_root(Equation * eq, FILE * out)
{
    if (is_zero(eq->a))
        fprintf(out, "\n%.2lfx%+.2lf = 0 has one root:\n\n"
                     "x = %.3lf\n", eq->b, eq->c, eq->roots[0]);
    else
        fprintf(out, "\n%.2lfx^2%+.2lfx%+.2lf = 0 has one root:\n\n"
                     "x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0]);
}


void print_two_roots(Equation * eq, FILE * out)
{
    fprintf(out, "%.2lfx^2%+.2lfx%+.2lf = 0 has two roots:\n\n"
                 "x = %.3lf, x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0], eq->roots[1]);
}


void print_infinite_roots(FILE * out)
{
    fprintf(out, "\n0 = 0 is an identity, infinite roots\n\n");
}


