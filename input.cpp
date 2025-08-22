#include <stdio.h>

#include "input.h"
#include "constants.h"
#include "utils.h"


bool get_coefficients(Equation * eq, Input_mode input_mode)
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

    while (true) {
        input_mode = getchar();

        if ('1' <= input_mode && input_mode <= '3' && check_input_buffer(stdin))
            switch (input_mode) {
                case '1': return KEYBOARD_INPUT;
                case '2': return INPUT_FROM_FILE;
                case '3': return QUIT;
                default: printf(RED "ERROR IN FUNCTION 'enter_input_mode': unnamed input mode\n" DEFAULT);
                         return QUIT;
            }

        printf(RED "Try again (1 / 2 / 3)\n" DEFAULT);

        clear_input_buffer();
    }
}


void enter_coefficients(Equation * eq)
{
    printf("Enter coefficients\n");

    while (true) {
        if (3 == scanf("%lf%lf%lf", &eq->a, &eq->b, &eq->c) && check_input_buffer(stdin))
            break;

        printf(RED "Try again\n" DEFAULT);

        clear_input_buffer();
    }
}


bool load_coefficients_from_file(Equation * eq)
{
    printf("Enter file name:\n");
    
    char file_name[MAX_BUFFER_LEN] = {};
    bool scan_status = enter_answer(file_name);

    if (UI_MODE == UI_ON)    
        clear_screen();

    if (!scan_status) {
        printf(RED "The file name is empty or too long\n\n" DEFAULT);
        return false;
    }

    FILE * in = fopen(file_name, "r"); 

    if (in == NULL) {
        printf(RED "Failed to open file '%s'\n\n" DEFAULT, file_name);
        return false;
    }
    
    int scanf_status = fscanf(in, "%lf%lf%lf", &eq->a, &eq->b, &eq->c);
    bool buffer_status = check_input_buffer(in);

    if (scanf_status == 3 && buffer_status && fclose(in) != EOF) {
        printf(GREEN "Import successful\n\n" DEFAULT);

        return true;
    } else {
        printf(RED "Failed to read coefficients from file '%s'\n\n" DEFAULT, file_name);

        return false;
    }
}
