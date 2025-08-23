#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include "output.h"
#include "constants.h"
#include "utils.h"


void print_into_file(Equation *eq)
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


bool get_output_file(FILE **out, char *file_name)
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
        printf(RED "Cannot export to file %s: %s\n\n" DEFAULT, file_name, strerror(errno));
        return false;
    }

    return true;
}


void print_equation(Equation *eq, FILE *out)
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


void print_no_roots(Equation *eq, FILE *out)
{
    if (is_zero(eq->a))
        fprintf(out, "\n%.2lf = 0 is not identical, no roots\n\n", eq->c);
    else
        fprintf(out, "\n%.2lfx^2%+.2lfx%+.2lf = 0 has a negative discriminant, no roots\n\n",
                eq->a, eq->b, eq->c); 
}


void print_one_root(Equation *eq, FILE *out)
{
    if (is_zero(eq->a))
        fprintf(out, "\n%.2lfx%+.2lf = 0 has one root:\n\n"
                     "x = %.3lf\n", eq->b, eq->c, eq->roots[0]);
    else
        fprintf(out, "\n%.2lfx^2%+.2lfx%+.2lf = 0 has one root:\n\n"
                     "x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0]);
}


void print_two_roots(Equation *eq, FILE *out)
{
    fprintf(out, "%.2lfx^2%+.2lfx%+.2lf = 0 has two roots:\n\n"
                 "x = %.3lf, x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0], eq->roots[1]);
}


void print_infinite_roots(FILE *out)
{
    fprintf(out, "\n0 = 0 is an identity, infinite roots\n\n");
}
