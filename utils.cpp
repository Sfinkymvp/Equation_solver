#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "constants.h"


bool is_zero(double number)
{
    return fabs(number) <= EPS;
}


void enter_answer(char * answer)
{
    fgets(answer, MAX_BUFFER_LEN, stdin);
    
    size_t len = strlen(answer);

    if (len > 0 && answer[len - 1] == '\n') {
        answer[len - 1] = '\0';
    } else {
        answer[0] = '\0';
        clear_input_buffer();
    }
}


bool check_agreement()
{
//  Возможные ответы пользователя, которые принимаются, как согласие
    const char * agreements[] = {"yes", "y", "ok", "okay", "1",
                                 "da", "true", "да", "окей", "ок"};
    const int len_agreements = sizeof(agreements) / sizeof(*agreements);    
    char answer[MAX_BUFFER_LEN] = {};
    
    enter_answer(answer);

    if (answer[0] == '\0')
        return false;

    for (int index = 0; index < len_agreements; index++)
        if (0 == strcasecmp(answer, agreements[index]))
            return true;

    return false;  
}


bool check_input_buffer(FILE * in)
{
    int c = 0;

    while ((c = getc(in)) != '\n' && c != EOF)
        if (!isspace(c))
            return false;

    return true;
}


bool is_file_available(char * file_name)
{
    FILE * in = fopen(file_name, "r");
    
    if (!in)
        return false;

    fclose(in);
    
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
