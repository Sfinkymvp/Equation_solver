#ifndef OUTPUT_H_
#define OUTPUT_H_


#include <stdio.h>

#include "constants.h"
#include "tests.h"


/// Записывает решение уравнения в указанный файл
/// @param eq Указатель на структуру с уравнением
void print_into_file(const Equation *eq);


/// Записывает результаты неудачных тестов в указанный файл
/// @param tests Динамический массив для хранения уравнений (тестов)
void print_tests_into_file(const Tests * tests);


/// Печатает сообщение о неудачном решении в указанный файл
/// @param test Тест с пользовательским и правильным решением
/// @param out Поток вывода
void print_failed_test(const Test_equation * test, FILE *out);


/// Выводит решения уравнения
/// @param eq Указатель на структуру с уравнением
/// @param out Поток вывода
void print_equation(const Equation *eq, FILE *out);


/// Печатает сообщение о ложном уравнении
/// @param eq Указатель на структуру с уравнением
/// @param out Поток вывода
void print_no_roots(const Equation *eq, FILE *out);


/// Печатает сообщение о наличии одного корня
/// @param eq Указатель на структуру с уравнением
/// @param out Поток вывода
void print_one_root(const Equation *eq, FILE *out);


///  Печатает сообщение о наличии двух корней
/// @param eq Указатель на структуру с уравнением
/// @param out Поток вывода
void print_two_roots(const Equation *eq, FILE *out);


/// Печатает сообщение о тождестве
/// @param out Поток вывода
void print_infinite_roots(FILE *out);


#endif  //  OUTPUT_H_
