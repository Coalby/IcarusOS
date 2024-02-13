BUILD_DIR := build
ISO_IMG := icarus.iso
OS_BIN := icarus.bin

# TODO: Terrible implementation! Find way for global variables?
# 		Violates DRY!!!
BOOT := $(BUILD_DIR)/arch/i386/
KERNEL := $(BUILD_DIR)/kernel/

OBJS := $(BOOT)/boot.o					\
		$(BOOT)/idt.o					\
		$(BOOT)/handlers.o				\
		$(BOOT)/interrupts.o			\
		$(BOOT)/system.o				\
		$(KERNEL)/kernel.o				\
		$(KERNEL)/utils.o

# TODO: Find way to make LD_SCRIPT more modular (Move it out to main dir?)
LD_SCRIPT := kernel/linker.ld
LD := i686-elf-gcc
LD_FLAGS := -T $(LD_SCRIPT) -o $(OS_BIN) -ffreestanding -O2 -nostdlib $(OBJS) -lgcc


.PHONY: all clean link qemu kernel isoimg test test-debug

all: isoimg

kernel:
	make -C kernel

link: kernel
	$(LD) $(LD_FLAGS)

isoimg: link
	mkdir -p iso/boot/grub
	cp $(OS_BIN) iso/boot/$(OS_BIN)
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_IMG) iso

qemu:
	qemu-system-i386 -cdrom $(ISO_IMG)

clean:
	make -C kernel clean
	rm -rf iso icarus.*

test: clean all qemu

test-debug: test
	qemu-system-i386 -cdrom $(ISO_IMG) -d int