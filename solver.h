#ifndef SOLVER_H_
#define SOLVER_H_


#include "constants.h"


/// Главная функция по решению уравнения
/// @param eq Указатель на структуру с уравнением
void solve_equation(Equation *eq);


/// Сортирует корни квадратного уравнения
/// @param eq Указатель на структуру с уравнением
void order_roots(Equation *eq);


/// Решает линейное уравнение
/// @param eq Указатель на структуру с уравнением
void solve_linear(Equation *eq);


/// Решает квадратное уравнение
/// @param eq Указатель на структуру с уравнением
void solve_quadratic(Equation *eq);


#endif  //  SOLVER_H_
