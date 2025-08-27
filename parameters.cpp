#include <stdio.h>

#include "parameters.h"
#include "constants.h"


const char HELP_SENTENCE[] = "Usage:\n"
                             "\t./solve [PARAMETERS]\n\n"
                             "Description:\n"
                             "\tEquation solver.\n"
                             "\tSolves equations of degree no higher than 2.\n\n"
                             "Input format:\n"
                             "\tFor coefficients:\n"
                             "\t\ta b c (Example: 5 1.32 -31)\n\n"
                             "\tFor tests:\n"
                             "\t\ta b c roots_count x1 x2 (Example: 1 -6 5 2 1 5)\n"
                             "\tIn place of 'roots_count' write:\n"
                             "\t\tIf no roots: '0'\n"
                             "\t\tIf one root: '1'\n"
                             "\t\tIf two roots: '2'\n"
                             "\t\tif infinite roots: '-1'\n\n";


static UI_mode_state ui_state = {UI_ON, 0};


static TEST_mode_state test_state = {TEST_OFF, 0};


static HELP_mode_state help_state = {HELP_OFF, 0};


UI_mode_switch get_ui_mode()
{
    return ui_state.mode; 
}


TEST_mode_switch get_test_mode()
{
    return test_state.mode;
}


HELP_mode_switch get_help_mode()
{
    return help_state.mode;
}


void change_ui_mode(UI_mode_switch new_ui_mode)
{
    if (ui_state.counter == 0) {
        ui_state.mode = new_ui_mode;
        ui_state.counter++;
    } else
        printf(RED "Repeated access to the UI_MODE variable is prohibited\n" DEFAULT);
}


void change_test_mode(TEST_mode_switch new_test_mode)
{
    if (test_state.counter == 0) {
        test_state.mode = new_test_mode;
        test_state.counter++;
    } else
        printf(RED "Repeated access to the TEST_MODE variable is prohibited\n" DEFAULT);
}


void change_help_mode(HELP_mode_switch new_help_mode)
{
    if (help_state.counter == 0) {
        help_state.mode = new_help_mode;
        help_state.counter++;
    } else
        printf(RED "Repeated access to the HELP_MODE variable is prohibited\n" DEFAULT);
}
