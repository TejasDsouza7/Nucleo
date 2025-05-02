#include "../include/keyboard.h"
#include "../include/print.h"
#include "../include/shell.h"
#include "../include/io.h"
#include <stdbool.h>


char input_buffer[128];
int input_index = 0;

char scancode_table[128] = {
    0,27,'1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
    'z','x','c','v','b','n','m',',','.','/', 0,'*', 0,' ',
};

void backspace() {
    extern int cursor_pos;
    if (cursor_pos > 0) {
        cursor_pos--;
        VIDEO_MEM[cursor_pos] = (' ' | (WHITE_ON_BLACK << 8));
    }
}

void print_prompt() {
    print_string("[OPS] ");
}

void input_loop() {
    bool shift = false;

    print_prompt();

    while (1) {
        if ((inb(0x64) & 1) == 0) continue;
        uint8_t sc = inb(0x60);

        if (sc & 0x80) {
            uint8_t key = sc & 0x7F;
            if (key == 42 || key == 54) shift = false;
        } else {
            if (sc == 42 || sc == 54) { 
                shift = true; 
                continue; 
            }
            if (sc == 14) { 
                if (input_index > 0) {
                    backspace();
                    input_index--;
                }
                continue;
            }
            if (sc == 28) { 
                print_char('\n');
                input_buffer[input_index] = '\0';
                handle_command(input_buffer);
                input_index = 0;
                print_prompt();
                continue;
            }

            char c = scancode_table[sc];
            if (c && input_index < (int)(sizeof(input_buffer) - 1)) {
                if (shift) {
                    if (c >= 'a' && c <= 'z') {
                        c -= 32; 
                    } else {
                        switch (c) {
                            case '1': c = '!'; break;
                            case '2': c = '@'; break;
                            case '3': c = '#'; break;
                            case '4': c = '$'; break;
                            case '5': c = '%'; break;
                            case '6': c = '^'; break;
                            case '7': c = '&'; break;
                            case '8': c = '*'; break;
                            case '9': c = '('; break;
                            case '0': c = ')'; break;
                            case '-': c = '_'; break;
                            case '=': c = '+'; break;
                            case '[': c = '{'; break;
                            case ']': c = '}'; break;
                            case '\\': c = '|'; break;
                            case ';': c = ':'; break;
                            case '\'': c = '"'; break;
                            case ',': c = '<'; break;
                            case '.': c = '>'; break;
                            case '/': c = '?'; break;
                            case '`': c = '~'; break;
                        }
                    }
                }
                print_char(c);
                input_buffer[input_index++] = c;
            }
        }
    }
}
