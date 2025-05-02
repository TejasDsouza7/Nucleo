#include "../include/string.h"

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}
void int_to_str(int value, char* str) {
    char temp[16];
    int i = 0;
    int is_negative = 0;

    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    if (value < 0) {
        is_negative = 1;
        value = -value;
    }

    while (value != 0) {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    }

    if (is_negative)
        temp[i++] = '-';

    int j = 0;
    while (i > 0)
        str[j++] = temp[--i];
    str[j] = '\0';
}

void strcat(char* dest, const char* src) {
    while (*dest) dest++;
    while (*src) *dest++ = *src++;
    *dest = '\0';
}
