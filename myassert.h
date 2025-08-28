#ifndef MYASSERT_H_
#define MYASSERT_H_


#include <stdarg.h>


/// Сообщения об ошибках
extern const char *error_messages[];


/// Коды ошибок (Для обращения в массив с сообщениями об ошибках)
typedef enum {
    ERR_NULL_PTR = 0,              ///< Указатель на NULL
    ERR_OUT_OF_RANGE = 1,          ///< Выход за границы массива или другого участка памяти
    ERR_OUT_OF_MEMORY = 2,         ///< Неудачное выделение памяти
    ERR_UNKNOWN = 3                ///< Неизвестный вид ошибки
} Error_code;


/// Обертка для скрытия констант
#define MY_ASSERT(condition, error_code, format, ...)             \
    my_assert(condition,                                          \
              #condition,                                         \
              __FILE__,                                           \
              __FUNCTION__,                                       \
              __LINE__,                                           \
              error_code,                                         \
              format,                                             \
              ##__VA_ARGS__) 


/// Собственный assert с возможностью указания типа ошибок, сообщений с различным назначением
/// @param condition Проверяемое выражение
/// @param cond_message Выражение в виде строки
/// @param file_name Имя файла, в котором найдена ошибка
/// @param function_name Имя функции, в которой найдена ошибка
/// @param line_number Номер строки, в которой найдена ошибка
/// @param error_code Код ошибки 
/// @param format Сообщение с желаемой информацией
/// @param ... Данные для заполнения форматной строки (Необязательные)
void my_assert(int condition,
               const char *cond_message,
               const char *file_name, 
               const char *function_name,
               const int line_number,
               Error_code error_code,
               const char *format,
               ...);


#endif  //  MYASSERT_H_
