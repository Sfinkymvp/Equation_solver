#ifndef INPUT_H_
#define INPUT_H_


#include "constants.h"
#include "utils.h"

//  Выбор способа получения коэффициентов
bool get_coefficients(Equation *, Input_mode);
//  Ввод пунктов меню
Input_mode enter_input_mode();
//  Ввод коэффициентов из стандартного ввода
void enter_coefficients(Equation *);
//  Чтение коэффициентов уравнения из файла
bool load_coefficients_from_file(Equation *);


#endif  //  INPUT_H_
