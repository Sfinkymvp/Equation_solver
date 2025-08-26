#ifndef UTILS_H_
#define UTILS_H_


#include <stdio.h>

#include "constants.h"
#include "tests.h"


/// Сравнивает число с плавающей точкой с нулем
/// @param number Число
/// @return true - число достаточно близко к нулю; false - недостаточно
bool is_equal(double number1, double number2);


/// Создает строковую константу с количеством корней уравнения
/// @param r_count Количество корней уравнения
/// @return Строковая константа количества корней уравнения
const char* r_count_to_str(Equation_roots_count r_count);


/// Обрабатывает аргументы командной строки
/// @param argc Количество параметров
/// @param argv Массив с параметрами
void parse_args(int argc, char **argv);


/// Удваивает длину динамического массива
/// @param tests Динамический массив для хранения уравнений (тестов)
/// @return true - длина удвоена; false - возникла проблема с памятью
bool resize_tests(Tests * tests);


/// Получает файл для чтения
/// @param in Указатель на поток ввода
/// @param file_name Имя файла для записи
/// @return true - поток успешно открыт; false - поток не открыт 
bool get_input_file(FILE **in, const char *file_name);


/// Получает файл для записи
/// @param out Указатель на поток вывода
/// @param file_name Имя файла для записи
/// @return true - поток успешно открыт; false - поток не открыт
bool get_output_file(FILE **out, const char *file_name);


/// Проверяет, содержит ли входной буффер только пробельные символы
/// @param in Входной поток
/// @return true - состоит из пробельных символов; false - не только из пробельных
bool is_buffer_whitespace_only(FILE *in);


/// Очищает входной буффер
void clear_input_buffer();


/// Очищает терминал
void clear_screen();


#endif  //  UTILS_H_
