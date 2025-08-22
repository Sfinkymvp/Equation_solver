#ifndef CONSTANTS_H_
#define CONSTANTS_H_

//  Для квадратного уравнения
const int MAX_ROOTS = 2;
//  Допустимая погрешность для чисел с плавающей точкой
const double EPS = 0.00000001;
//  Допустимая длина имени файла
const int MAX_BUFFER_LEN = 100;

//  Цвета для выделения ошибок и статусов
#define RED "\033[31m"
#define GREEN "\033[32m"
#define DEFAULT "\e[0m" 

//  Количество корней уравнения для структуры
typedef enum {
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    INFINITE_ROOTS = -1,
} Equation_roots_count;

//  Режим ввода в меню
typedef enum {
    KEYBOARD_INPUT = '1',
    INPUT_FROM_FILE = '2',
    QUIT = '3'
} Input_mode;
        
//  Режим пользовательского интерфейса
typedef enum {
    UI_OFF = 0,
    UI_ON = 1
} UI_mode_switch;


typedef struct {
//  Общий вид квадратного уравнения:  ax^2 + bx + c, линейного: bx + c (при а = 0)
    double a, b, c;
//  Количество корней уравнения
    Equation_roots_count r_count;
//  Массив для хранения корней
    double roots[MAX_ROOTS];
} Equation;


extern UI_mode_switch UI_MODE;

#endif  //  CONSTANTS_H_
