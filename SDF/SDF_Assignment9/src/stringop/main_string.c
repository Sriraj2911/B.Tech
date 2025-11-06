#include <stdio.h>
#include "stringop.h"

int main() {
    char str[] = "Hello World";
    to_uppercase(str);
    printf("Uppercase: %s\n", str);
    to_lowercase(str);
    printf("Lowercase: %s\n", str);
    return 0;
}
