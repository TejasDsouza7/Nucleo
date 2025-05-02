[bits 32]

section .multiboot
align 4
    dd 0x1BADB002
    dd 0x0
    dd -0x1BADB002

section .text
global start
extern kernel_main

start:
    mov esp, stack_top
    call kernel_main
.hang:
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 4096
stack_top:
