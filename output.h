#ifndef OUTPUT_H_
#define OUTPUT_H_


#include <stdio.h>

#include "constants.h"


/// Записывает решение уравнения в пользовательский файл
/// @param eq Указатель на структуру с уравнением
void print_into_file(Equation *eq);


/// Получает файл для записи
/// @param out Указатель на поток вывода
/// @param file_name Имя файла для записи
/// @return true - поток успешно открыт; false - поток не открыт
bool get_output_file(FILE **out, char *file_name);


/// Выводит решения уравнения
/// @param eq Указатель на структуру с уравнением
/// @param out Поток вывода
void print_equation(Equation *eq, FILE *out);


/// Печатает сообщение о ложном уравнении
/// @param eq Указатель на структуру с уравнением
/// @param out Поток вывода
void print_no_roots(Equation *eq, FILE *out);


/// Печатает сообщение о наличии одного корня
/// @param eq Указатель на структуру с уравнением
/// @param out Поток вывода
void print_one_root(Equation *eq, FILE *out);


///  Печатает сообщение о наличии двух корней
/// @param eq Указатель на структуру с уравнением
/// @param out Поток вывода
void print_two_roots(Equation *eq, FILE *out);


/// Печатает сообщение о тождестве
/// @param out Поток вывода
void print_infinite_roots(FILE *out);


#endif  //  OUTPUT_H_
