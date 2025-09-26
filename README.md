# Nucleo

Nucleo is a simple x86 operating system kernel designed for educational purposes. It provides basic functionality such as keyboard input, mouse handling, and a shell interface with a few built-in commands.

## Features
- **Keyboard Input**: Supports text input and basic key handling, including shift for uppercase and special characters.
- **Mouse Support**: Tracks mouse movement and prints random numbers & letters in screen.
- **Shell Interface**: A simple command-line interface with built-in commands.
- **Real-Time Clock**: Displays the current time (UTC+5:30) only.
- **Basic Graphics**: Text-based output using VGA.

## Built-In Commands
- `/help`: Displays a list of available commands.
- `/hello`: Prints a greeting message.
- `/clear`: Clears the screen.
- `/reboot`: Reboots the system.
- `/shutdown`: Halts the system.
- `/about`: Displays information about the kernel.
- `/version`: Displays the kernel version.
- `/time`: Displays the current time (UTC+5:30).

## Project Structure
```
Nucleo/
├── boot/
│   ├── boot.asm          # Assembly code for bootloader
│   ├── grub/
│   │   └── grub.cfg      # GRUB configuration file
├── kernel/
│   ├── include/          # Header files
│   │   ├── idt.h
│   │   ├── io.h
│   │   ├── keyboard.h
│   │   ├── mouse.h
│   │   ├── print.h
│   │   ├── shell.h
│   │   ├── string.h
│   │   └── time.h
│   ├── linker/
│   │   └── link.ld       # Linker script
│   ├── src/              # Source files
│       ├── idt.c
│       ├── kernel.c
│       ├── keyboard.c
│       ├── mouse.c
│       ├── print.c
│       ├── shell.c
│       ├── string.c
│       └── time.c
└── Makefile              # Build system
```

## Prerequisites
- **Cross Compiler**: `i686-elf-gcc` and `i686-elf-ld`
- **GRUB Tools**: `grub-mkrescue`
- **Emulator**: QEMU or any x86 emulator

## Building the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/Tejasdsouza/Nucleo.git
   cd Nucleo
   ```
2. Build the kernel:
   ```bash
   make
   ```
3. Create a bootable ISO:
   ```bash
   make iso
   ```

## Running the Kernel
Run the kernel using QEMU:
```bash
make run
```

## Cleaning the Build
To clean the build artifacts:
```bash
make clean
```

## Author
Tejas Dsouza
