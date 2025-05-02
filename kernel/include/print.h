#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>

#define WHITE_ON_BLACK 0x0F
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define VIDEO_MEM ((uint16_t*)0xB8000)

extern int cursor_pos;

void print_char(char c);
void print_string(const char* str);
void clear_screen();

#endif
