#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include "output.h"
#include "input.h"
#include "constants.h"
#include "utils.h"
#include "tests.h"


void print_into_file(const Equation *eq)
{
    assert(eq != NULL);

    char file_name[MAX_BUFFER_LEN] = {};

    if (!enter_file_name(file_name))
        return;

    FILE *out = NULL;
    
    if (!get_output_file(&out, file_name)) 
        return;

    print_equation(eq, out);

    if (fclose(out) == EOF)
        printf(RED "The solution was not written: %s\n\n" DEFAULT, strerror(errno)); 
    else
        printf(GREEN "The solution was successfully written.\n\n" DEFAULT);
}


void print_tests_into_file(const Tests * tests)
{
    assert(tests->equations != NULL);

    char file_name[MAX_BUFFER_LEN] = {};

    if (!enter_file_name(file_name))
        return;

    FILE *out = NULL;
    
    if (!get_output_file(&out, file_name)) 
        return;

    for (int index = 0; index < tests->len; index++)
        if (tests->equations[index].status == TEST_ERR)
            print_failed_test(&tests->equations[index], out);

    if (fclose(out) == EOF)
        printf(RED "Incorrect solutions were not written to the file\n" DEFAULT);
    else 
        printf(GREEN "Incorrect solutions were written to the file\n" DEFAULT);
}


void print_failed_test(const Test_equation * test, FILE *out)
{
    print_equation(&test->ref, out);

    fprintf(out, "In a user solution: r_count = %s, x1 = %lf, x2 = %lf\n\n",
    r_count_to_str(test->eq.r_count), test->eq.roots[0], test->eq.roots[1]);
}


void print_equation(const Equation *eq, FILE *out)
{   
    assert(out != NULL);

    switch (eq->r_count) {
        case NO_ROOTS: print_no_roots(eq, out); break;
        case ONE_ROOT: print_one_root(eq, out); break;
        case TWO_ROOTS: print_two_roots(eq, out); break;
        case INFINITE_ROOTS: print_infinite_roots(out); break;
        default: fprintf(out, "ERROR IN FUNCTION 'print_equation': enum parameter not processed\n"); break;
    }
}


void print_no_roots(const Equation *eq, FILE *out)
{
    if (is_equal(eq->a, 0))
        fprintf(out, "\n%.2lf = 0 is not identical, no roots\n", eq->c);
    else
        fprintf(out, "\n%.2lfx^2%+.2lfx%+.2lf = 0 has a negative discriminant, no roots\n",
                eq->a, eq->b, eq->c); 
}


void print_one_root(const Equation *eq, FILE *out)
{
    if (is_equal(eq->a, 0))
        fprintf(out, "\n%.2lfx%+.2lf = 0 has one root:\n\n"
                     "x = %.3lf\n", eq->b, eq->c, eq->roots[0]);
    else
        fprintf(out, "\n%.2lfx^2%+.2lfx%+.2lf = 0 has one root:\n\n"
                     "x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0]);
}


void print_two_roots(const Equation *eq, FILE *out)
{
    fprintf(out, "%.2lfx^2%+.2lfx%+.2lf = 0 has two roots:\n\n"
                 "x = %.3lf, x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0], eq->roots[1]);
}


void print_infinite_roots(FILE *out)
{
    fprintf(out, "\n0 = 0 is an identity, infinite roots\n");
}
