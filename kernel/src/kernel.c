#include "../include/print.h"
#include "../include/io.h"
#include "../include/mouse.h"
#include "../include/keyboard.h"
#include "../include/idt.h"
#include "../include/time.h"


void draw_progress_bar(int percent) {
    int total_blocks = 20;
    int filled = (percent * total_blocks) / 100;
    int row = 12;
    int col = (80 - total_blocks - 2) / 2;
    int pos = row * 80 + col;
    VIDEO_MEM[pos++] = ('[' | (WHITE_ON_BLACK << 8));
    for (int i = 0; i < total_blocks; i++) {
        char c = (i < filled) ? '#' : ' ';
        VIDEO_MEM[pos++] = (c | (WHITE_ON_BLACK << 8));
    }
    VIDEO_MEM[pos++] = (']' | (WHITE_ON_BLACK << 8));
}

void loading_screen() {
    clear_screen();
    print_string("\n[BOOT] Initializing Tactical Kernel Systems...\n");
    print_string("[UNIT] Nucleo OPS TERMINAL\n");
    print_string("[CHK] Establishing visual uplink...\n");

    for (int i = 0; i <= 100; i += 10) {
        draw_progress_bar(i);
        for (volatile int j = 0; j < 27000000; j++);
    }

    print_string("\n[BOOT] System online. Awaiting directives.\n\n");
}

void kernel_main() {
    loading_screen();
    clear_screen();

    pic_remap();
    load_idt();
    mouse_init();


    draw_cursor(40, 12, 'X');
    print_string("[OPS] Welcome to Nucleo Tactical Kernel. Type /help\n");

    input_loop();
}


