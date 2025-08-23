#ifndef UTILS_H_
#define UTILS_H_


#include <stdio.h>


/// Сравнивает число с плавающей точкой с нулем
/// @param number Число
/// @return Результат сравнения 
bool is_zero(double number);


/// Получает ответ пользователя
/// @param Строка для записи ответа
/// @return Результат успешности записи 
bool enter_answer(char *answer);


/// Получает имя файла от пользователя
/// @param Строка для записи имени файла
/// @return Результат успешности записи 
bool enter_file_name(char *file_name);


/// Предлагает пользователю дать согласие на действие
/// @return Согласие / несогласие пользователя 
bool check_agreement();


/// Проверяет, содержит ли входной буффер только пробельные символы
/// @param Входной поток
/// @return Результат проверки 
bool is_buffer_whitespace_only(FILE *in);


/// Очищает входной буффер
void clear_input_buffer();


/// Очищает терминал
void clear_screen();


#endif  //  UTILS_H_
