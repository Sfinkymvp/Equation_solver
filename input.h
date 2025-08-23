#ifndef INPUT_H_
#define INPUT_H_


#include "constants.h"
#include "utils.h"


/// Производит ветвление по режиму ввода коэффициентов
/// @param eq Указатель на структуру с уравнением 
/// @param input_mode Режим ввода коэффициентов
/// @return Успешно ли получены коэффициенты 
bool get_coefficients(Equation *eq, Input_mode input_mode);


/// Получает от пользователя режим для ввода коэффициентов
/// @return Режим ввода
Input_mode enter_input_mode();


/// Получает коэффициенты уравнения от пользователя
/// @param eq Указатель на структуру с уравнением
void enter_coefficients(Equation *eq);


/// Получает коэффициенты уравнения из пользоватеского файла
/// @param eq Указатель на структуру с уравнением
/// @return Успешно ли получены коэффициенты из файла
bool load_coefficients_from_file(Equation *eq);


#endif  //  INPUT_H_
