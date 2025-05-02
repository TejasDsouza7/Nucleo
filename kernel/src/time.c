#include <stdint.h>
#include "../include/time.h"
#include "../include/io.h"        
#include "../include/print.h" 
#include "../include/string.h"  

static uint8_t read_cmos(uint8_t reg) {
    outb(0x70, reg);
    return inb(0x71);
}

static uint8_t bcd_to_bin(uint8_t bcd) {
    return ((bcd / 16) * 10) + (bcd & 0x0F);
}

void print_rtc_time() {
    uint8_t hour = read_cmos(0x04);
    uint8_t min  = read_cmos(0x02);
    uint8_t sec  = read_cmos(0x00);
    uint8_t bcd_mode = !(read_cmos(0x0B) & 0x04);



    if (bcd_mode) {
        hour = bcd_to_bin(hour);
        min  = bcd_to_bin(min);
        sec  = bcd_to_bin(sec);
    }
    
    hour += 5;
    min += 30;

   if (min >= 60) {
    min -= 60;
    hour += 1;
   }
   if (hour >= 24) {
    hour -= 24;
   }

     char buf[32];
    buf[0] = '\0';
    
    char h[4], m[4], s[4];
    int_to_str(hour, h);
    int_to_str(min, m);
    int_to_str(sec, s);
    
    strcat(buf, "\n[TIME] ");
    strcat(buf, h);
    strcat(buf, ":");
    strcat(buf, m);
    strcat(buf, ":");
    strcat(buf, s);
    strcat(buf, "\n");
    
    print_string(buf);    
}
