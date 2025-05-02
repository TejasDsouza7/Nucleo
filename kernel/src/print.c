#include "../include/print.h"

int cursor_pos = 0;

void print_char(char c) {
    if (c == '\n') {
        cursor_pos += SCREEN_WIDTH - (cursor_pos % SCREEN_WIDTH);
    } else {
        VIDEO_MEM[cursor_pos++] = (c | (WHITE_ON_BLACK << 8));
    }
}

void print_string(const char* str) {
    while (*str) print_char(*str++);
}

void clear_screen() {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        VIDEO_MEM[i] = (' ' | (WHITE_ON_BLACK << 8));
    }
    cursor_pos = 0;
}
