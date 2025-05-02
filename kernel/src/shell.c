#include "../include/shell.h"
#include "../include/print.h"
#include "../include/io.h"
#include "../include/string.h"
#include "../include/time.h"
#include "../include/keyboard.h"

void handle_command(const char* input) {
    if (!strcmp(input, "/help")) {
        print_string("\n[INFO] Commands: /help /hello /clear /reboot /shutdown /about /version /time \n");
    } else if (!strcmp(input, "/hello")) {
        print_string("\n[OPS] Stay sharp, soldier.\n");
    } else if (!strcmp(input, "/clear")) {
        clear_screen();
    } else if (!strcmp(input, "/reboot")) {
        print_string("\n[SYS] Rebooting unit...\n");
        outb(0x64, 0xFE);
    } else if (!strcmp(input, "/shutdown")) {
        clear_screen();
        print_string("\n[SYS] Mission terminated.\n");
        print_string("[SYS] Nucleo Kernel going dark.\n");
        print_string("[SYS] Await new deployment...\n");
        for (;;) __asm__ volatile ("hlt");
    } else if (!strcmp(input, "/about")) {
        print_string("\n[OPS] Nucleo Kernel - T-170 Edition by Tejas\n");
    } else if (!strcmp(input, "/version")) {
        print_string("\n[OPS] Version 1.0 - Combat Ready\n");
    } else if (!strcmp(input_buffer, "/time")) {
        print_rtc_time();
    } else {
        print_string("\n[ERROR] Unknown command.\n");
    }
}
