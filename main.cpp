#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "utils.h"
#include "solver.h"
#include "input.h"
#include "output.h"
#include "arts.h"


int main(int argc, char **argv)
{
    Equation eq = {};

    if (argc == 2 && strcmp(argv[1], "-ui") == 0)
        UI_MODE = UI_OFF;

    if (UI_MODE == UI_ON) {
        clear_screen();
        print_hello();
    }

    while (true) {
        Input_mode input_mode = enter_input_mode();

        if (input_mode == QUIT)
            break;

        if (!get_coefficients(&eq, input_mode))
            continue;

        solve_equation(&eq);

        print_equation(&eq, stdout);
       
        printf("\nDo you want to write the solution to a file? (y/n)\n");

        if (check_agreement()) {
            print_into_file(&eq);
            continue;
        }
        
        if (UI_MODE == UI_ON)
            clear_screen();
    }

    if (UI_MODE == UI_ON) {
        print_byebye(); 
    }

    return 0;
}
