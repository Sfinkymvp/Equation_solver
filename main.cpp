#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "parameters.h"
#include "utils.h"
#include "solver.h"
#include "input.h"
#include "output.h"
#include "tests.h"
#include "arts.h"


int main(int argc, char **argv)
{
    parse_args(argc, argv); 

    Equation eq = {};

    if (get_help_mode() == HELP_ON) {
        printf("%s", HELP_MESSAGE);
        return 0;
    }

    if (get_ui_mode() == UI_ON) {
        clear_screen();
        print_hello();
    }

    if (get_test_mode() == TEST_OFF) {
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
            
            if (get_ui_mode() == UI_ON)
                clear_screen();
        }
    } else {
        Tests tests = {NULL, 0, 0};

        if (load_tests_from_file(&tests)) {
            run_tests(&tests);

            is_tests_correct(&tests);
        }

        if (tests.equations != NULL)
            free(tests.equations);
    }

    if (get_ui_mode() == UI_ON) {
        print_byebye(); 
    }

    return 0;
}
