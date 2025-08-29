#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "input.h"
#include "constants.h"
#include "parameters.h"
#include "solver.h"
#include "utils.h"
#include "tests.h"
#include "myassert.h"


bool enter_answer(char *answer)
{
    MY_ASSERT(answer != NULL, ERR_NULL_PTR, "'answer' must not point to null");

    fgets(answer, MAX_BUFFER_LEN, stdin);
    
    size_t len = strlen(answer);

    if (len > 0 && answer[len - 1] == '\n') {
        answer[len - 1] = '\0';
        return true;
    } else {
        answer[0] = '\0';
        clear_input_buffer(stdin);
        return false;
    }
}


bool enter_file_name(char *file_name)
{
    MY_ASSERT(file_name != NULL, ERR_NULL_PTR, "'file_name' must not point to null");

    printf("Enter file name:\n");
    
    bool enter_status = enter_answer(file_name);

    if (get_mode(UI) == MODE_ON)    
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
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");

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
    printf("Select the coefficient input mode:\n"
           "1 - Keyboard input\n"
           "2 - Reading from file\n"
           "3 - Quit\n\n");

    while (true) {
        char input_mode = 0;
        int read_status = scanf(" %c", &input_mode);

        if (read_status == EOF)
            return QUIT;

        clear_input_buffer(stdin);

        switch (input_mode) {
            case '1': return KEYBOARD_INPUT;
            case '2': return INPUT_FROM_FILE;
            case '3': return QUIT;
            default: printf(RED "Enter a valid character (1 / 2 / 3)\n" DEFAULT);
                     continue;
        }
    }
}


void enter_coefficients(Equation *eq)
{
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");

    printf("Enter coefficients\n");

    while (true) {
        int read_count = scanf("%lf %lf %lf", &eq->a, &eq->b, &eq->c);

        if (read_count == EOF)
            break;

        if (read_count == 3 && is_buffer_whitespace_only(stdin)) {
            if (is_coefficients_correct(eq))
                break;
            else {
                printf(RED "Without NaN and INF, Please)\n" DEFAULT);
                continue;
            }
        }

        printf(RED "Try again\n" DEFAULT);

        clear_input_buffer(stdin);
    }
}


bool load_coefficients_from_file(Equation *eq)
{
    MY_ASSERT(eq != NULL, ERR_NULL_PTR, "'eq' must point to a structure");

    char file_name[MAX_BUFFER_LEN] = {};
    
    if (!enter_file_name(file_name))
        return false;

    FILE *in = get_input_file(file_name);

    if (in == NULL)
        return false;
 
    MY_ASSERT(in != NULL, ERR_NULL_PTR, "The output stream 'in' must exist");

    int scanf_status = fscanf(in, "%lf%lf%lf", &eq->a, &eq->b, &eq->c);
    bool buffer_status = is_buffer_whitespace_only(in);

    if (scanf_status == 3 && is_coefficients_correct(eq) && buffer_status && fclose(in) != EOF) {
        printf(GREEN "Import successful\n\n" DEFAULT);
        return true;
    } else {
        printf(RED "Failed to read coefficients from file '%s'\n\n" DEFAULT, file_name);
        return false;
    }
}


bool enter_user_tests(Tests * tests, FILE * in)
{
    MY_ASSERT(tests != NULL, ERR_NULL_PTR, "'tests' must point to structure");
    MY_ASSERT(in != NULL, ERR_NULL_PTR, "The output stream 'in' must exist");

    for (tests->len = 0; true; tests->len++) {
        if (tests->len >= tests->cap)
            if (!resize_tests(tests)) {
                printf(RED "Memory allocation error\n" DEFAULT);
                return false;
            } 

        Test_equation *test = &tests->equations[tests->len];

        MY_ASSERT(test != NULL, ERR_NULL_PTR, "'test' must point to structure");

        int roots_count = 0; 
        int read_count = fscanf(in, "%lf %lf %lf %d %lf %lf",
        &test->eq.a, &test->eq.b, &test->eq.c, &roots_count, &test->eq.roots[0], &test->eq.roots[1]);

        if (read_count == EOF) {
            order_roots(&test->eq);
            return true;
        }

        if (!is_test_correct(test, roots_count, read_count, in))
            return false;
    }
}


bool load_tests_from_file(Tests * tests)
{
    MY_ASSERT(tests != NULL, ERR_NULL_PTR, "'tests' must point to structure");
    char file_name[MAX_BUFFER_LEN] = {};

    if (!enter_file_name(file_name))
        return false;

    FILE *in = get_input_file(file_name);

    if (in == NULL)
        return false;

    MY_ASSERT(in != NULL, ERR_NULL_PTR, "The output stream 'in' must exist");

    return enter_user_tests(tests, in) && fclose(in) == 0;
}
