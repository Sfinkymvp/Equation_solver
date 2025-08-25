#include <stdio.h>

#include "parameters.h"


static UI_mode_state ui_state = {UI_ON, 0};


static TEST_mode_state test_state = {TEST_OFF, 0};


UI_mode_switch get_ui_mode()
{
    return ui_state.mode; 
}


TEST_mode_switch get_test_mode()
{
    return test_state.mode;
}


void change_ui_mode(UI_mode_switch new_ui_mode)
{
    if (ui_state.counter == 0) {
        ui_state.mode = new_ui_mode;
        ui_state.counter++;
    } else
        printf("Repeated access to the UI_MODE variable is prohibited\n");
}


void change_test_mode(TEST_mode_switch new_test_mode)
{
    if (test_state.counter == 0) {
        test_state.mode = new_test_mode;
        test_state.counter++;
    } else
        printf("Repeated access to the TEST_MODE variable is prohibited\n");
}
