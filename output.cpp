#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "output.h"
#include "input.h"
#include "constants.h"
#include "utils.h"
#include "tests.h"
#include "myassert.h"


void print_into_file(const Equation *eq)
{
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");

    char file_name[MAX_BUFFER_LEN] = {};

    if (!enter_file_name(file_name))
        return;

    FILE *out = get_output_file(file_name);
    
    if (out == NULL)
        return;

    MY_ASSERT(out != NULL, ERR_NULL_PTR, "The output stream 'out' must exist");

    print_equation(eq, out);

    if (fclose(out) == EOF)
        printf(RED "The solution was not written: %s\n\n" DEFAULT, strerror(errno)); 
    else
        printf(GREEN "The solution was successfully written.\n\n" DEFAULT);
}


void print_tests_into_file(const Tests * tests)
{
    MY_ASSERT(tests != NULL, ERR_NULL_PTR, "'tests' must point to structure");
    MY_ASSERT(tests->equations != NULL, ERR_NULL_PTR, "Dynamic array with tests must exist"); 
    MY_ASSERT(tests->len > 0, ERR_OUT_OF_RANGE, "Number of tests: %d, it should be positive", tests->len);

    char file_name[MAX_BUFFER_LEN] = {};

    if (!enter_file_name(file_name))
        return;

    FILE *out = get_output_file(file_name);
    
    if (out == NULL)
        return;

    MY_ASSERT(out != NULL, ERR_NULL_PTR, "The output stream 'out' must exist");

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
    MY_ASSERT(test != NULL, ERR_NULL_PTR, "'test' should point to test");
    MY_ASSERT(out != NULL, ERR_NULL_PTR, "The output stream 'out' must exist");

    fprintf(out, "In the equation with coefficients\n"
                 "a = %.5lf, b = %.5lf, c = %.5lf\n",
    test->ref.a, test->ref.b, test->ref.c);

    fprintf(out, "In a program solution: r_count = %s, x1 = %lf, x2 = %lf\n",
    r_count_to_str(test->ref.r_count), test->ref.roots[0], test->ref.roots[1]);

    fprintf(out, "In a user solution: r_count = %s, x1 = %lf, x2 = %lf\n\n",
    r_count_to_str(test->eq.r_count), test->eq.roots[0], test->eq.roots[1]);
}


void print_equation(const Equation *eq, FILE *out)
{   
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");
    MY_ASSERT(out != NULL, ERR_NULL_PTR, "The output stream 'out' must exist");

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
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");
    MY_ASSERT(out != NULL, ERR_NULL_PTR, "The output stream 'out' must exist");

    if (is_equal(eq->a, 0))
        fprintf(out, "%.2lf = 0 is not identical, no roots\n", eq->c);
    else
        fprintf(out, "%.2lfx^2%+.2lfx%+.2lf = 0 has a negative discriminant, no roots\n",
                eq->a, eq->b, eq->c); 
}


void print_one_root(const Equation *eq, FILE *out)
{
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");
    MY_ASSERT(out != NULL, ERR_NULL_PTR, "The output stream 'out' must exist");

    if (is_equal(eq->a, 0))
        fprintf(out, "%.2lfx%+.2lf = 0 has one root:\n"
                     "x = %.3lf\n", eq->b, eq->c, eq->roots[0]);
    else
        fprintf(out, "%.2lfx^2%+.2lfx%+.2lf = 0 has one root:\n"
                     "x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0]);
}


void print_two_roots(const Equation *eq, FILE *out)
{
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");
    MY_ASSERT(out != NULL, ERR_NULL_PTR, "The output stream 'out' must exist");

    fprintf(out, "%.2lfx^2%+.2lfx%+.2lf = 0 has two roots:\n"
                 "x = %.3lf, x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0], eq->roots[1]);
}


void print_infinite_roots(FILE *out)
{
    MY_ASSERT(out != NULL, ERR_NULL_PTR, "The output stream 'out' must exist");

    fprintf(out, "0 = 0 is an identity, infinite roots\n");
}
