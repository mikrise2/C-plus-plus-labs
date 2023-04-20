#include "test_str.h"
#include "str.h"
#include <assert.h>
#include <string.h>

void test_my_strlen() {
    assert(my_strlen("22") == 2);
    assert(my_strlen("12345") == 5);
    assert(my_strlen("") == 0);
}

void test_my_strcmp() {
    int x = my_strcmp("abc", "ab");
    int y = my_strcmp("ab", "abc");
    int z = my_strcmp("abc", "abc");
    assert(1 == (x < 0 ? -1 : x == 0 ? 0 : 1));
    assert(-1 == (y < 0 ? -1 : y == 0 ? 0 : 1));
    assert(0 == (z < 0 ? -1 : z == 0 ? 0 : 1));
}

void test_my_strcat() {
    char *str1 = "fasfasfas";
    char str2[20] = "afasfasfas";
    assert(0 == strcmp(strcat(str2, str1), "afasfasfasfasfasfas"));
}

void test_my_strcpy() {
    char *str1 = "fasfasfas";
    char str2[20] = "afasfasfas";
    assert(0 == strcmp(strcpy(str2, str1), "fasfasfas"));
}
