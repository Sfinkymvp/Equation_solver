#include <stdio.h>

#include "parameters.h"
#include "constants.h"
#include "myassert.h"


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
                             "\t--ui    Disable standard user interface\n"
                             "\t--help  Show this help message\n"
                             "\t--test  Enable test mode\n";


Mode_switch statuses[] = {MODE_ON,    
                          MODE_OFF,
                          MODE_OFF};


Mode_switch get_mode(Options option)
{
    MY_ASSERT(UI <= option && option <= TEST, ERR_OUT_OF_RANGE, "Enum 'Options' value out of bounds");

    return statuses[option];
}


void change_mode(Options option, Mode_switch new_mode)
{
    MY_ASSERT(UI <= option && option <= TEST, ERR_OUT_OF_RANGE, "Enum 'Options' value out of bounds");
    MY_ASSERT(MODE_OFF <= new_mode && new_mode <= MODE_ON, ERR_OUT_OF_RANGE, "Enum 'Mode_switch value out of bounds");

    statuses[option] = new_mode;
}
