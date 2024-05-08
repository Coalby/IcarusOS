BUILD_DIR 	:= build
ISO_IMG 	:= icarus.iso
OS_BIN 		:= icarus.bin

BOOT_BUILD 		:= $(BUILD_DIR)/arch/i386/
KERNEL_BUILD 	:= $(BUILD_DIR)/kernel/
DRIVERS_BUILD 	:= $(BOOT_BUILD)/drivers

OBJS := $(BOOT_BUILD)/boot.o					\
		$(BOOT_BUILD)/idt.o						\
		$(BOOT_BUILD)/handlers.o				\
		$(BOOT_BUILD)/interrupts.o				\
		$(BOOT_BUILD)/lib.o						\
		$(BOOT_BUILD)/pit.o						\
		$(BOOT_BUILD)/physical_memory_manager.o \
		$(BOOT_BUILD)/system.o					\
		$(DRIVERS_BUILD)/keyboard.o				\
		$(KERNEL_BUILD)/kernel.o

# TODO: Find way to make LD_SCRIPT more modular (Move it out to main dir?)
LD_SCRIPT := src/linker.ld
LD := i686-elf-gcc
LD_FLAGS := -T $(LD_SCRIPT) -o $(OS_BIN) -ffreestanding -O2 -nostdlib $(OBJS) -lgcc


.PHONY: all clean link qemu src isoimg test test-debug

all: isoimg

src:
	make -C src

link: src
	$(LD) $(LD_FLAGS)

isoimg: link
	mkdir -p iso/boot/grub
	cp $(OS_BIN) iso/boot/$(OS_BIN)
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_IMG) iso

clean:
	make -C src clean
	rm -rf iso icarus.*

test: clean all
	qemu-system-i386 -cdrom $(ISO_IMG)

test-debug: clean all
	qemu-system-i386 -s -S -cdrom $(ISO_IMG)