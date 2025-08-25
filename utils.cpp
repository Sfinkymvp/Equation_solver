#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "utils.h"
#include "parameters.h"
#include "constants.h"


bool is_equal(double number1, double number2)
{
    return fabs(number1 - number2) <= EPS;
}


const char *r_count_to_str(Equation_roots_count r_count)
{
    switch (r_count) {
        case NO_ROOTS: return "NO_ROOTS";
        case ONE_ROOT: return "ONE_ROOT";
        case TWO_ROOTS: return "TWO_ROOTS";
        case INFINITE_ROOTS: return "INFINITE_ROOTS";
        default: return "UNKNOWN";
    }
}


void parse_args(int argc, char **argv)
{
    for (int index = 0; index < argc; index++) {
        if (0 == strcmp(argv[index], "-ui") && get_ui_mode() == UI_ON)
            change_ui_mode(UI_OFF);

        if (0 == strcmp(argv[index], "-test") && get_test_mode() == TEST_OFF)
            change_test_mode(TEST_ON);
    }
}


bool is_buffer_whitespace_only(FILE *in)
{
    assert(in != NULL);

    int c = 0;

    while ((c = getc(in)) != '\n' && c != EOF)
        if (!isspace(c))
            return false;

    return true;
}


void clear_input_buffer()
{
    int c = 0;
    
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}


void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
