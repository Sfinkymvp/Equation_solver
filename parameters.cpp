#include <stdio.h>

#include "parameters.h"
#include "constants.h"


const char HELP_MESSAGE[] = "Usage:\n"
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
                             "\t\tIf infinite roots: '-1'\n\n"
                             "Options:\n"
                             "\t--help  Show this help message\n"
                             "\t--test  Enable test mode\n"
                             "\t--ui    Disable standard user interface\n";


static UI_mode_switch ui_mode = UI_ON;


static TEST_mode_switch test_mode = TEST_OFF;


static HELP_mode_switch help_mode = HELP_OFF;


UI_mode_switch get_ui_mode()
{
    return ui_mode;
}


TEST_mode_switch get_test_mode()
{
    return test_mode;
}


HELP_mode_switch get_help_mode()
{
    return help_mode;
}


void change_ui_mode(UI_mode_switch new_ui_mode)
{
    static int ui_change_counter = 0;

    if (ui_change_counter == 0) {
        ui_mode = new_ui_mode;
        ui_change_counter++;
    } else
        printf(RED "Repeated access to the UI_MODE variable is prohibited\n" DEFAULT);
}


void change_test_mode(TEST_mode_switch new_test_mode)
{
    static int test_change_counter = 0;

    if (test_change_counter == 0) {
        test_mode = new_test_mode;
        test_change_counter++;
    } else
        printf(RED "Repeated access to the TEST_MODE variable is prohibited\n" DEFAULT);
}


void change_help_mode(HELP_mode_switch new_help_mode)
{
    static int help_change_counter = 0;

    if (help_change_counter == 0) {
        help_mode = new_help_mode;
        help_change_counter++;
    } else
        printf(RED "Repeated access to the HELP_MODE variable is prohibited\n" DEFAULT);
}
