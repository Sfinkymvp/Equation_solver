#ifndef SOLVER_H_
#define SOLVER_H_


#include "constants.h"

//  Главная функция работы с уравнением
void solve_equation(Equation *);
//  Сортирует корни квадратного уравнения
void order_roots(Equation *);
//  Решение линейного уравнения
void solve_linear(Equation *);
//  Решение квадратного уравнения
void solve_quadratic(Equation *);


#endif  //  SOLVER_H_
