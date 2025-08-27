#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "input.h"
#include "constants.h"
#include "parameters.h"
#include "solver.h"
#include "utils.h"
#include "tests.h"


bool enter_answer(char *answer)
{
    fgets(answer, MAX_BUFFER_LEN, stdin);
    
    size_t len = strlen(answer);

    if (len > 0 && answer[len - 1] == '\n') {
        answer[len - 1] = '\0';
        return true;
    } else {
        answer[0] = '\0';
        clear_input_buffer();
        return false;
    }
}


bool enter_file_name(char *file_name)
{
    printf("Enter file name:\n");
    
    bool enter_status = enter_answer(file_name);

    if (get_ui_mode() == UI_ON)    
        clear_screen();

    if (!enter_status) {
        printf(RED "The file name is empty or too long\n\n" DEFAULT);
        return false;
    }

    return true;
}


bool check_agreement()
{
    const char *agreements[] = {"yes", "y", "ok", "okay", "1",
                                 "da", "true", "да", "окей", "ок"};
    const int len_agreements = sizeof(agreements) / sizeof(*agreements);    
    char answer[MAX_BUFFER_LEN] = {};
    
    if (!enter_answer(answer))
        return false;

    for (int index = 0; index < len_agreements; index++)
        if (0 == strcasecmp(answer, agreements[index]))
            return true;

    return false;  
}


bool get_coefficients(Equation *eq, Input_mode input_mode)
{
    switch (input_mode) {
        case KEYBOARD_INPUT: enter_coefficients(eq);
                  return true;
        case INPUT_FROM_FILE: return load_coefficients_from_file(eq);
        case QUIT: printf(RED "ERROR IN FUNCTION 'get_coefficients': QUIT in the switch\n" DEFAULT);
                   return false;
        default: printf(RED "ERROR IN FUNCTION 'get_coefficients': unknown input mode: %c\n" DEFAULT, input_mode);
                 return false;
    }
    
}


Input_mode enter_input_mode()
{
    int input_mode = 0;

    printf("Select the coefficient input mode:\n"
           "1 - Keyboard input\n"
           "2 - Reading from file\n"
           "3 - Quit\n\n");

    while (true) {
        input_mode = getchar();

        if (input_mode == EOF)
            return QUIT;

        if (is_buffer_whitespace_only(stdin))
            switch (input_mode) {
                case '1': return KEYBOARD_INPUT;
                case '2': return INPUT_FROM_FILE;
                case '3': return QUIT;
                default: printf(RED "Enter a valid character (1 / 2 / 3)\n" DEFAULT);
                         clear_input_buffer();
                         continue;
            }

        printf(RED "Enter one character (1 / 2 / 3)\n" DEFAULT);
        clear_input_buffer();
    }
}


void enter_coefficients(Equation *eq)
{
    printf("Enter coefficients\n");

    while (true) {
        if (3 == scanf("%lf%lf%lf", &eq->a, &eq->b, &eq->c) && is_buffer_whitespace_only(stdin))
            break;

        if (getchar() == EOF)
            break;

        printf(RED "Try again\n" DEFAULT);

        clear_input_buffer();
    }
}


bool load_coefficients_from_file(Equation *eq)
{
    char file_name[MAX_BUFFER_LEN] = {};
    
    if (!enter_file_name(file_name))
        return false;

    FILE *in = NULL;

    if (!get_input_file(&in, file_name))
        return false;

    int scanf_status = fscanf(in, "%lf%lf%lf", &eq->a, &eq->b, &eq->c);
    bool buffer_status = is_buffer_whitespace_only(in);

    if (scanf_status == 3 && buffer_status && fclose(in) != EOF) {
        printf(GREEN "Import successful\n\n" DEFAULT);
        return true;
    } else {
        printf(RED "Failed to read coefficients from file '%s'\n\n" DEFAULT, file_name);
        return false;
    }
}


bool enter_tests(Tests * tests, FILE * in)
{
    for (tests->len = 0; true; tests->len++) {
        if (tests->len >= tests->cap)
            if (!resize_tests(tests)) {
                printf(RED "Memory allocation error\n" DEFAULT);
                return false;
            } 

        int roots_count = 0; 
        int read_count = fscanf(in, "%lf %lf %lf %d %lf %lf",
        &tests->equations[tests->len].eq.a, &tests->equations[tests->len].eq.b, &tests->equations[tests->len].eq.c,
        &roots_count, &tests->equations[tests->len].eq.roots[0],
        &tests->equations[tests->len].eq.roots[1]);

        if (!choose_roots_count(&tests->equations[tests->len].eq.r_count, roots_count)) {
            printf(RED "incorrect number of roots in one of the equations from the file\n" DEFAULT);
            return false;
        }

        if (read_count == EOF) {
            order_roots(&tests->equations[tests->len].eq);
            return true;
        }

        int ch = 0;

        while ((ch = getc(in)) == ' ' || ch == '\t')
            ;

        if ((ch != '\n' && ch != EOF) || read_count != 6) {
            printf(RED "The file contains lines that do not match the format:\n"
                   "a b c roots_count x1 x2\n" DEFAULT);
            return false;
        }
      }
}


bool load_tests_from_file(Tests * tests)
{
    char file_name[MAX_BUFFER_LEN] = {};

    if (!enter_file_name(file_name))
        return false;

    FILE *in = NULL;

    if (!get_input_file(&in, file_name))
        return false;

    return enter_tests(tests, in) && fclose(in) == 0;
}
