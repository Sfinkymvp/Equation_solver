#ifndef PARAMETERS_H_
#define PARAMETERS_H_


/// Текст с информацией о программе (Параметр --help)
extern const char HELP_MESSAGE[];


/// Режим работы опции
typedef enum {
    MODE_OFF = 0,        ///< Выключен
    MODE_ON = 1          ///< Включен
} Mode_switch;


/// Доступные опции
typedef enum {
    UI = 0,              ///< Пользовательский интерфейс (По умолчанию включен)
    HELP = 1,            ///< Меню справки (Отдельный режим)
    TEST = 2             ///< Режим работы с тестами (Отдельный режим)
} Options;
   

/// Позволяет узнать режим работы опции
/// @param mode Опция, режим работы которой нужно узнать
/// @return Режим работы опции
Mode_switch get_mode(Options option);


/// Меняет режим работы нужной опции
/// @param mode Опция, режим работы которой нужно изменить
/// @param new_mode Новый режим работы опции
void change_mode(Options option, Mode_switch new_mode);


#endif  //  PARAMETERS_H_
