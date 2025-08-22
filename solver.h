#ifndef SOLVER_H_
#define SOLVER_H_


#include "constants.h"

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


#endif  //  SOLVER_H_
