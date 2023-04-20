#include "str.h"

int my_strlen(const char *s) {
    const char *c = s;
    while (*c)
        c++;
    return c - s;
}

char *my_strcpy(char *restrict s1, const char *restrict s2) {
    const char *f2 = s2;
    char *f1 = s1;
    while (*f2)
        *s1++ = *f2++;
    *s1 = '\0';
    return f1;
}

char *my_strcat(char *restrict s1, const char *restrict s2) {
    const char *f2 = s2;
    char *f1 = s1;
    while (*s1)
        s1++;
    while (*f2)
        *s1++ = *f2++;
    *s1 = '\0';
    return f1;
}

int my_strcmp(const char *s1, const char *s2) {
    const char *f1 = s1;
    const char *f2 = s2;
    while (*f1 && *f2 && (*f1 == *f2)) {
        f1++;
        f2++;
    }
    return *f1 - *f2;
}
