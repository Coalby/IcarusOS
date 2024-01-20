KERNEL_BUILD_DIR = ../build/kernel
KERNEL_DIR = kernel

BOOT_BUILD_DIR := ../build/bootloader
BOOT_DIR = arch/i386

AS := i686-elf-as

CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c

KERNEL_SRC = $(wildcard $(KERNEL_DIR)/*.c)
KERNEL_OBJS = $(patsubst %.c, $(KERNEL_BUILD_DIR)/%.o, $(KERNEL_SRC))

BOOTLOADER_SRCS := $(wildcard $(BOOT_DIR)/*.s)
BOOTLOADER_OBJS := $(patsubst %.s, $(BOOT_BUILD_DIR)/%.o, $(BOOTLOADER_SRCS))

all: $(KERNEL_OBJS) $(BOOTLOADER_OBJS)

$(KERNEL_BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(BOOT_BUILD_DIR)/%.o: %.s
	$(AS) $< -o $@

clean:
	rm $(KERNEL_BUILD_DIR)/*
	rm $(BOOT_BUILD_DIR)/*