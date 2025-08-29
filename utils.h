#ifndef UTILS_H_
#define UTILS_H_


#include <stdio.h>

#include "constants.h"
#include "tests.h"


/// Сравнивает число с плавающей точкой с нулем
/// @param number Число
/// @return true - число достаточно близко к нулю; false - недостаточно
bool is_equal(double number1, double number2);


/// Проверяет корректность коэффициентов (Не NAN и не INFINITY)
/// @param eq Указатель на структуру с уравнением 
/// @return true - коэффициенты корректны; false - коэффициенты некорректны
bool is_coefficients_correct(Equation *eq);


/// Проверяет пользовательский тест на корректность
/// @param test Указатель на структуру с тестом
/// @param roots_count Указанное пользователем количество корней
/// @param read_count Количество считанных из потока чисел
/// @param in Поток ввода
/// @return true - тест корректен, данные записаны; false - тест некорректен
bool is_test_correct(Test_equation *test, int roots_count, int read_count, FILE *in);


/// Создает строковую константу с количеством корней уравнения
/// @param r_count Количество корней уравнения
/// @return Строковая константа количества корней уравнения
const char* r_count_to_str(Equation_roots_count r_count);


/// Выбирает количество корней уравнения
/// @param r_count Указатель на количество корней уравнения
/// @param selected_number Вводимое пользователем количество корней уравнения
/// @return true - количество корней корректно; false - количество корней некорректно
bool choose_roots_count(Equation_roots_count *r_count, int selected_number);


/// Обрабатывает аргументы командной строки
/// @param argc Количество параметров
/// @param argv Массив с параметрами
void parse_args(int argc, char **argv);


/// Удваивает длину динамического массива
/// @param tests Динамический массив для хранения уравнений (тестов)
/// @return true - длина удвоена; false - возникла проблема с памятью
bool resize_tests(Tests * tests);


/// Получает файл для чтения
/// @param file_name Имя файла для записи
/// @return При успешном открытии - поток, иначе NULL
FILE *get_input_file(const char *file_name);


/// Получает файл для записи
/// @param file_name Имя файла для записи
/// @return При успешном открытии - поток, иначе NULL
FILE *get_output_file(const char *file_name);


/// Проверяет, содержит ли входной буффер только пробельные символы
/// @param in Входной поток
/// @return true - состоит из пробельных символов; false - не только из пробельных
bool is_buffer_whitespace_only(FILE *in);


/// Очищает входной буффер
/// @param in Входной поток
void clear_input_buffer(FILE *in);


/// Очищает терминал
void clear_screen();


#endif  //  UTILS_H_
