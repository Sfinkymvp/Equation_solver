#ifndef UTILS_H_
#define UTILS_H_


#include <stdio.h>


//  Сравнивание числа с плавающей точкой с нулем
bool is_zero(double);
//  Ввод ответа из стандартного ввода
bool enter_answer(char * answer);
//  Выводит результат ответа пользователя (Да/Нет)
bool check_agreement();
//  Проверяет входной буффер на наличие символов, не являющихся пробельными
bool check_input_buffer(FILE *);
//  Очищает входной буффер
void clear_input_buffer();
//  Очищает терминал
void clear_screen();


#endif  //  UTILS_H_
