#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>

#include "utils.h"
#include "parameters.h"
#include "constants.h"
#include "tests.h"
#include "input.h"


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
        if (0 == strcmp(argv[index], "--ui") && get_ui_mode() == UI_ON)
            change_ui_mode(UI_OFF);

        if (0 == strcmp(argv[index], "--test") && get_test_mode() == TEST_OFF)
            change_test_mode(TEST_ON);

        if (0 == strcmp(argv[index], "--help") && get_help_mode() == HELP_OFF)
            change_help_mode(HELP_ON);
    }
}


bool resize_tests(Tests *tests)
{
    if (tests->cap == 0) {
        tests->cap = START_TESTS_CAP;
        tests->equations = (Test_equation*)calloc(START_TESTS_CAP, sizeof(Test_equation));
    } else {
        tests->cap *= 2;
        Test_equation *temp = (Test_equation*)realloc(tests->equations, (long unsigned int)tests->cap * sizeof(Test_equation));

        if (temp != NULL) {
            tests->equations = temp;
        } else {
            printf(RED "Memory allocation error\n" DEFAULT);
            return false;
        }
    }

    for (int index = tests->cap / 2; index < tests->cap; index++)
        memset(&tests->equations[index], 0, sizeof(Test_equation));

    return true;
}


bool get_input_file(FILE **in, const char *file_name)
{
    *in = fopen(file_name, "r"); 

    if (*in == NULL) {
        printf(RED "Failed to open file '%s': %s\n\n" DEFAULT, file_name, strerror(errno));
        return false;
    }

    return true;
}

 
bool get_output_file(FILE **out, const char *file_name)
{
    assert(file_name != NULL);

    FILE *test = fopen(file_name, "r");

    if (test != NULL) {
        printf("The file '%s' already exists. Do you want to overwrite it? (y/n)\n\n", file_name);

        if (!check_agreement()) {
            fclose(test);
            return false;
        }
    }
             
    if (test == NULL)
        *out = fopen(file_name, "w");
    else
        *out = freopen(file_name, "w", test);

    if (*out == NULL) {
        if (test != NULL)
            fclose(test);

        printf(RED "Cannot export to file %s: %s\n\n" DEFAULT, file_name, strerror(errno));
        return false;
    }

    return true;
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
