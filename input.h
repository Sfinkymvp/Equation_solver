#ifndef INPUT_H_
#define INPUT_H_


#include "constants.h"
#include "tests.h"
#include "utils.h"


/// Получает ответ пользователя
/// @param answer Строка для записи ответа
/// @return true - ответ записан успешно; false - ответ не записан
bool enter_answer(char *answer);


/// Получает имя файла от пользователя
/// @param file_name Строка для записи имени файла
/// @return true - имя записано успешно; false - имя не записано
bool enter_file_name(char *file_name);


/// Предлагает пользователю дать согласие на действие
/// @return true - согласие; false - несогласие
bool check_agreement();


/// Производит ветвление по режиму ввода коэффициентов
/// @param eq Указатель на структуру с уравнением 
/// @param input_mode Режим ввода коэффициентов
/// @return true - коэффициенты записаны; false - коэффициенты не записаны
bool get_coefficients(Equation *eq, Input_mode input_mode);


/// Получает от пользователя режим для ввода коэффициентов
/// @return Режим ввода коэффициентов 
Input_mode enter_input_mode();


/// Получает коэффициенты уравнения от пользователя
/// @param eq Указатель на структуру с уравнением
void enter_coefficients(Equation *eq);


/// Получает коэффициенты уравнения из пользовательского файла
/// @param eq Указатель на структуру с уравнением
/// @return true - коэффициенты получены из файла; false - коэффициенты не получены
bool load_coefficients_from_file(Equation *eq);


/// Считывает пользовательские тесты из указанного файла
/// @param tests Динамический массив для хранения уравнений (тестов)
/// @param in Поток ввода
/// @return true - тесты успешно считаны; false - тесты не считаны
bool enter_user_tests(Tests * tests, FILE * in);


/// Загружает пользовательские тесты из файла
/// @param tests Динамический массив для хранения уравнений (тестов)
/// @return true - все тесты получены; false - тесты не получены
bool load_tests_from_file(Tests * tests);


#endif  //  INPUT_H_
