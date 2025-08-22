#include <stdio.h>

#include "output.h"
#include "constants.h"
#include "utils.h"


void print_into_file(Equation * eq)
{
    printf("Enter file name:\n");

    char file_name[MAX_BUFFER_LEN] = {};
    enter_answer(file_name);

    if (UI_MODE == UI_ON)
        clear_screen();

    if (file_name[0] == '\0') {
        printf(RED "The file name is empty or too long\n\n" DEFAULT);
        return;
    }

    FILE * test = fopen(file_name, "r");

    if (test != NULL) {
        printf("The file '%s' already exists.\n"
               "Do you want to overwrite it? (y/n)\n\n", file_name);

        if (!check_agreement()) {
            fclose(test);
            return;
        }
    }
             
    FILE * out = NULL;

    if (test == NULL)
        out = fopen(file_name, "w");
    else
        out = freopen(file_name, "w", test);

    if (out == NULL) {
        printf(RED "Cannot export to file %s\n\n" DEFAULT, file_name);
        return; 
    }

    print_equation(eq, out);

    if (fclose(out) == EOF)
        printf(RED "The solution was not written to the file.\n\n" DEFAULT); 
    else
        printf(GREEN "The solution has been successfully written to the file.\n\n" DEFAULT);
}


void print_equation(Equation * eq, FILE * out)
{   
    switch (eq->r_count) {
        case NO_ROOTS: print_no_roots(eq, out); break;
        case ONE_ROOT: print_one_root(eq, out); break;
        case TWO_ROOTS: print_two_roots(eq, out); break;
        case INFINITE_ROOTS: print_infinite_roots(out); break;
        default: fprintf(out, "ERROR IN FUNCTION 'print_equation': enum parameter not processed\n"); break;
    }
}


void print_no_roots(Equation * eq, FILE * out)
{
    if (is_zero(eq->a))
        fprintf(out, "\n%.2lf = 0 is not identical, no roots\n\n", eq->c);
    else
        fprintf(out, "\n%.2lfx^2%+.2lfx%+.2lf = 0 has a negative discriminant, no roots\n\n",
                eq->a, eq->b, eq->c); 
}


void print_one_root(Equation * eq, FILE * out)
{
    if (is_zero(eq->a))
        fprintf(out, "\n%.2lfx%+.2lf = 0 has one root:\n\n"
                     "x = %.3lf\n", eq->b, eq->c, eq->roots[0]);
    else
        fprintf(out, "\n%.2lfx^2%+.2lfx%+.2lf = 0 has one root:\n\n"
                     "x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0]);
}


void print_two_roots(Equation * eq, FILE * out)
{
    fprintf(out, "%.2lfx^2%+.2lfx%+.2lf = 0 has two roots:\n\n"
                 "x = %.3lf, x = %.3lf\n", eq->a, eq->b, eq->c, eq->roots[0], eq->roots[1]);
}


void print_infinite_roots(FILE * out)
{
    fprintf(out, "\n0 = 0 is an identity, infinite roots\n\n");
}
