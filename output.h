#ifndef OUTPUT_H_
#define OUTPUT_H_


#include <stdio.h>

#include "constants.h"

//  Записывает решение уравнения в файл 
void print_into_file(Equation *);
//  Вывод корней уравнения
void print_equation(Equation *, FILE *);
//  Выводит сообщение о тождественно ложном уравнении
void print_no_roots(Equation *, FILE *);
//  Выводит сообщение о наличии одного корня
void print_one_root(Equation *, FILE *);
//  Выводит сообщение о наличии двух корней
void print_two_roots(Equation *, FILE *);
//  Выводит сообщение о тождестве
void print_infinite_roots(FILE *);


#endif  //  OUTPUT_H_
