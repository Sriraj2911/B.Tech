#include <ctype.h>
#include "stringop.h"

void to_uppercase(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

void to_lowercase(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}
