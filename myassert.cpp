#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "myassert.h"


const char *error_messages[] = {
    "Pointer to NULL",
    "Out of range",
    "Out of memory",
    "Unknown error"
};


void my_assert(int condition,
               const char *cond_message,
               const char *file_name,
               const char *function_name,
               const int line_number,
               Error_code error_code,
               const char *format,
               ...)
{
    if (!condition) {
        printf("Assertion failed!\n"
               "File: %s\n"
               "Function: %s\n"
               "Line: %d\n"
               "Condition: %s\n"
               "Error: %s\n",
               file_name, function_name, line_number, cond_message, error_messages[error_code]);

        if (format) {
            va_list args;
            va_start(args, format);

            vprintf(format, args);
            printf("\n");

            va_end(args);
        }

        abort();
    }
}
