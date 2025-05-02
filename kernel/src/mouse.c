#include "../include/mouse.h"
#include "../include/io.h"
#include "../include/print.h"

int mouse_x = 40, mouse_y = 12;
uint8_t mouse_cycle = 0;
int8_t mouse_packet[3];

void draw_cursor(int x, int y, char c) {
    VIDEO_MEM[y * 80 + x] = (c | (WHITE_ON_BLACK << 8));
}

void mouse_handler() {
    uint8_t status = inb(0x64);
    if (!(status & 0x01)) return;

    int8_t data = inb(0x60);
    mouse_packet[mouse_cycle++] = data;

    if (mouse_cycle == 3) {
        mouse_cycle = 0;

        draw_cursor(mouse_x, mouse_y, ' ');
        mouse_x += mouse_packet[1];
        mouse_y -= mouse_packet[2];

        if (mouse_x < 0) mouse_x = 0;
        if (mouse_x >= 80) mouse_x = 79;
        if (mouse_y < 0) mouse_y = 0;
        if (mouse_y >= 25) mouse_y = 24;

        draw_cursor(mouse_x, mouse_y, 'X');
        outb(0x20, 0x20);
        outb(0xA0, 0x20);
    }
}

void mouse_init() {
    outb(0xA8, 0x00);
    outb(0x64, 0x20); while (!(inb(0x64) & 1));
    uint8_t status = inb(0x60) | 2;
    outb(0x64, 0x60);
    outb(0x60, status);
    outb(0x64, 0xD4); outb(0x60, 0xF4);
}
