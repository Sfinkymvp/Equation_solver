#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "utils.h"
#include "constants.h"


bool is_zero(double number)
{
    return fabs(number) <= EPS;
}


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

    if (UI_MODE == UI_ON)    
        clear_screen();

    if (!enter_status) {
        printf(RED "The file name is empty or too long\n\n" DEFAULT);
        return false;
    }

    return true;
}


bool check_agreement()
{
//  Возможные ответы пользователя, которые принимаются, как согласие
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


bool is_buffer_whitespace_only(FILE *in)
{
    assert(in != NULL);

    int c = 0;

    while ((c = getc(in)) != '\n' && c != EOF)
        if (!isspace(c))
            return false;

    return true;
}


void clear_input_buffer()
{
    int c = 0;
    
    while ((c = getchar()) != '\n' && c != EOF)
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
