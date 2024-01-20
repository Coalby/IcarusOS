BUILD_DIR := build
ISO_IMG := icarus.iso

BOOT := $(BUILD_DIR)/bootloader/boot.o
KERNEL := $(BUILD_DIR)/kernel/kernel.o

# TODO: Find way to make LD_SCRIPT more modular
LD_SCRIPT := kernel/arch/i386/linker.ld
LD := i686-elf-gcc
LD_FLAGS := -T $(LD_SCRIPT) -o icarus.bin -ffreestanding -O2 -nostdlib $(BOOT) $(KERNEL) -lgcc

.PHONY: all link isoimg clean kernel qemu

all: isoimg

kernel:
	make -C kernel

link: kernel
	$(LD) $(LD_FLAGS)

isoimg: link 
	mkdir -p iso/boot/grub
	cp icarus.bin iso/boot/icarus.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_IMG) iso

qemu:
	qemu-system-i386 -cdrom icarus.iso 

clean:
	rm -rf iso icarus.*
	make -C bootloader clean
	make -C kernel clean
