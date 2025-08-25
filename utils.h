#ifndef UTILS_H_
#define UTILS_H_


#include <stdio.h>

#include "constants.h"


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


/// Проверяет, содержит ли входной буффер только пробельные символы
/// @param in Входной поток
/// @return true - состоит из пробельных символов; false - не только из пробельных
bool is_buffer_whitespace_only(FILE *in);


/// Очищает входной буффер
void clear_input_buffer();


/// Очищает терминал
void clear_screen();


#endif  //  UTILS_H_
