CROSS_COMPILE ?= i686-elf-

AS      = $(CROSS_COMPILE)as
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
GRUB_MKISOIMAGE = grub-mkrescue

CFLAGS  = -ffreestanding -O2 -Wall -Wextra -std=gnu11 -m32 -c
LDFLAGS = -ffreestanding -O2 -nostdlib -m32

BUILD_DIR   = build
SRC_DIR     = kernel/src
LINK_DIR    = kernel/linker
BOOT_DIR    = boot
ISO_DIR     = iso

SRC_FILES   = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES   = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

.PHONY: all run clean iso

all: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: $(BOOT_DIR)/boot.o $(OBJ_FILES) $(LINK_DIR)/link.ld
	@mkdir -p $(BUILD_DIR)
	$(LD) -T $(LINK_DIR)/link.ld -o $@ $(BOOT_DIR)/boot.o $(OBJ_FILES)

$(BOOT_DIR)/boot.o: $(BOOT_DIR)/boot.asm
	nasm -f elf32 $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR) Nucleo.iso

iso: all
	@mkdir -p $(ISO_DIR)/boot/grub
	cp $(BUILD_DIR)/kernel.bin $(ISO_DIR)/boot/kernel.bin
	echo 'set timeout=2' > $(ISO_DIR)/boot/grub/grub.cfg
	echo 'set default=2' >> $(ISO_DIR)/boot/grub/grub.cfg
	echo 'menuentry "Nucleo Kernel" {' >> $(ISO_DIR)/boot/grub/grub.cfg
	echo '    multiboot /boot/kernel.bin' >> $(ISO_DIR)/boot/grub/grub.cfg
	echo '}' >> $(ISO_DIR)/boot/grub/grub.cfg
	$(GRUB_MKISOIMAGE) -o Nucleo.iso $(ISO_DIR)

run: iso
	qemu-system-x86_64 -cdrom Nucleo.iso

