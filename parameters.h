#ifndef PARAMETERS_H_
#define PARAMETERS_H_


/// Текст с информацией о программе (Параметр --help)
extern const char HELP_MESSAGE[];


/// Режим работы расширенного пользовательского интерфейса
typedef enum {
    UI_OFF = 0,        ///< Выключен (Параметр --ui)
    UI_ON = 1          ///< Включен
} UI_mode_switch;


/// Режим работы с пользовательскими тестами
typedef enum {
    TEST_OFF = 0,      ///< Выключен
    TEST_ON = 1        ///< Включен (Параметр --test)
} TEST_mode_switch;


/// Режим работы с меню помощи
typedef enum {
    HELP_OFF = 0,      ///< Меню выключено
    HELP_ON = 1        ///< Меню включено (параметр --help)
} HELP_mode_switch;


/// Позволяет узнать режим работы пользовательского интерфейса
/// @return Режим работы пользовательского интерфейса
UI_mode_switch get_ui_mode();


/// Позволяет узнать режим работы с пользовательскими тестами
/// @return Режим работы с пользовательскими тестами
TEST_mode_switch get_test_mode();


/// Позволяет узнать режим работы меню помощи
/// @return Режим работы с меню помощи
HELP_mode_switch get_help_mode();


/// Единожды меняет режим работы пользовательского интерфейса
/// @param Новый режим работы пользовательского интерфейса
void change_ui_mode(UI_mode_switch new_ui_mode);


/// Единожды меняет режим работы с пользовательскими тестами
/// @param Новый режим работы с пользовательскими тестами
void change_test_mode(TEST_mode_switch new_test_mode);


/// Единожды меняет режим работы меню помощи
/// @param Новый режим работы меню помощи
void change_help_mode(HELP_mode_switch new_help_mode);


#endif  //  PARAMETERS_H_
