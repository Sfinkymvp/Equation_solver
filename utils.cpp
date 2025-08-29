#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "utils.h"
#include "parameters.h"
#include "constants.h"
#include "tests.h"
#include "input.h"
#include "myassert.h"


bool is_equal(double number1, double number2)
{
    return fabs(number1 - number2) <= EPS;
}


bool is_coefficients_correct(Equation *eq)
{
    return isfinite(eq->a) && isfinite(eq->b) && isfinite(eq->c);
}


bool is_test_correct(Test_equation *test, int roots_count, int read_count, FILE *in)
{
    MY_ASSERT(test != NULL, ERR_NULL_PTR, "'test' should point to test");
    MY_ASSERT(in != NULL, ERR_NULL_PTR, "The output stream 'in' must exist");

    if (!is_coefficients_correct(&test->eq)) {
        printf(RED "incorrect coefficients\n" DEFAULT);
        return false;
    } 

    if (!choose_roots_count(&test->eq.r_count, roots_count)) {
        printf(RED "incorrect number of roots in one of the equations from the file\n" DEFAULT);
        return false;
    }

    int ch = 0;

    while ((ch = getc(in)) == ' ' || ch == '\t')
        ;

    if ((ch != '\n' && ch != EOF) || read_count != 6) {
        printf(RED "The file contains lines that do not match the format:\n"
               "a b c roots_count x1 x2\n" DEFAULT);
        return false;
    }

    return true;
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


bool choose_roots_count(Equation_roots_count *r_count, int selected_number)
{
    MY_ASSERT(r_count != NULL, ERR_NULL_PTR, "'r_count' shouldn't point to NULL");

    switch (selected_number) {
        case -1: *r_count = INFINITE_ROOTS; return true;
        case 0: *r_count = NO_ROOTS; return true;
        case 1: *r_count = ONE_ROOT; return true;
        case 2: *r_count = TWO_ROOTS; return true;
        default: *r_count = NO_ROOTS; return false;
    }
}


void parse_args(int argc, char **argv)
{
    MY_ASSERT(argv != NULL, ERR_NULL_PTR, "'argv' shoudn't point to NULL");

    for (int index = 0; index < argc; index++) {
        if (0 == strcmp(argv[index], "--ui") && get_mode(UI) == MODE_ON)
            change_mode(UI, MODE_OFF);

        if (0 == strcmp(argv[index], "--help") && get_mode(HELP) == MODE_OFF)
            change_mode(HELP, MODE_ON);

        if (0 == strcmp(argv[index], "--test") && get_mode(TEST) == MODE_OFF)
            change_mode(TEST, MODE_ON);
    }
}


bool resize_tests(Tests *tests)
{
    MY_ASSERT(tests != NULL, ERR_NULL_PTR, "'tests' must point to structure");

    Test_equation *temp = NULL;

    if (tests->cap == 0) {
        tests->cap = START_TESTS_CAP;
        temp = (Test_equation*)calloc(START_TESTS_CAP, sizeof(Test_equation));
    } else {
        MY_ASSERT(tests->equations != NULL, ERR_NULL_PTR, "Dynamic array with tests must exist"); 

        tests->cap *= 2;
        temp = (Test_equation*)realloc(tests->equations, (long unsigned int)tests->cap * sizeof(Test_equation));
    }

    if (temp != NULL) {
        tests->equations = temp;
    } else {
        printf(RED "Memory allocation error\n" DEFAULT);
        return false;
    }

    for (int index = tests->cap / 2; index < tests->cap; index++)
        memset(&tests->equations[index], 0, sizeof(Test_equation));

    return true;
}


FILE *get_input_file(const char *file_name)
{
    MY_ASSERT(file_name != NULL, ERR_NULL_PTR, "'file_name' must exist");

    FILE *in = fopen(file_name, "r"); 

    if (in == NULL) {
        printf(RED "Failed to open file '%s': %s\n\n" DEFAULT, file_name, strerror(errno));
        return NULL;
    }

    return in;
}

 
FILE *get_output_file(const char *file_name)
{
    MY_ASSERT(file_name != NULL, ERR_NULL_PTR, "'file_name' must exist");
    
    FILE *test = fopen(file_name, "r");

    if (test != NULL) {
        printf("The file '%s' already exists. Do you want to overwrite it? (y/n)\n\n", file_name);

        if (!check_agreement()) {
            fclose(test);
            return NULL;
        }
    }
        
    FILE *out = NULL;

    if (test == NULL)
        out = fopen(file_name, "w");
    else
        out = freopen(file_name, "w", test);

    if (out == NULL) {
        if (test != NULL)
            fclose(test);

        printf(RED "Cannot export to file %s: %s\n\n" DEFAULT, file_name, strerror(errno));
        return NULL;
    }

    return out;
}


bool is_buffer_whitespace_only(FILE *in)
{
    MY_ASSERT(in != NULL, ERR_NULL_PTR, "The output stream 'in' must exist");

    int c = 0;

    while ((c = getc(in)) != '\n' && c != EOF)
        if (!isspace(c)) 
            return false;

    return true;
}


void clear_input_buffer(FILE *in)
{
    MY_ASSERT(in != NULL, ERR_NULL_PTR, "The output stream 'in' must exist");

    int c = 0;
    
    while ((c = getc(in)) != '\n' && c != EOF)
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
