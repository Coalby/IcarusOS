HOSTARCH:=i386
ARCHDIR:=arch/$(HOSTARCH)

BUILD_DIR:=../build
KERNEL_DIR = kernel
BOOT_DIR = arch/i386

AS := i686-elf-as

CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c

KERNEL_SRC = $(wildcard $(KERNEL_DIR)/*.c)
KERNEL_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(KERNEL_SRC))

BOOT_SRCS := $(wildcard $(BOOT_DIR)/*.s)
BOOT_OBJS := $(patsubst %.s, $(BUILD_DIR)/%.o, $(BOOT_SRCS))

.PHONY: all clean

all: | $(BUILD_DIR) $(KERNEL_OBJS) $(BOOT_OBJS)

$(BUILD_DIR)/$(KERNEL_DIR)/%.o: $(KERNEL_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(BOOT_DIR)/%.o: $(BOOT_DIR)/%.s
	$(AS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/$(KERNEL_DIR)
	mkdir -p $(BUILD_DIR)/$(BOOT_DIR)

clean:
	rm -rf $(BUILD_DIR)
