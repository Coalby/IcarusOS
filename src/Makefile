HOSTARCH 	:= i386
ARCHDIR 	:= arch/$(HOSTARCH)

BUILD_DIR 	:= ../build
KERNEL_DIR 	:= kernel
BOOT_DIR 	:= $(ARCHDIR)
DRIVER_DIR 	:= $(BOOT_DIR)/drivers
INCLUDE_DIR := include

AS 			:= i686-elf-as
CC 			:= i686-elf-gcc

CFLAGS 		:= -std=gnu99 -O0 -g -ffreestanding -O2 -Wall -Wextra -I $(KERNEL_DIR)/$(INCLUDE_DIR) -I $(BOOT_DIR)/$(INCLUDE_DIR) -I $(DRIVER_DIR)/$(INCLUDE_DIR) -c

# TODO: Fix these terrible object variables
KERNEL_SRC 	:= $(wildcard $(KERNEL_DIR)/*.c)
KERNEL_OBJS := $(patsubst $(KERNEL_DIR)/%.c, $(BUILD_DIR)/$(KERNEL_DIR)/%.o, $(KERNEL_SRC))

BOOT_SRCS_S := $(wildcard $(BOOT_DIR)/*.s)
BOOT_OBJS_S := $(patsubst $(BOOT_DIR)/%.s, $(BUILD_DIR)/$(BOOT_DIR)/%.o, $(BOOT_SRCS_S))

BOOT_SRCS_C := $(wildcard $(BOOT_DIR)/*.c)
BOOT_OBJS_C := $(patsubst $(BOOT_DIR)/%.c, $(BUILD_DIR)/$(BOOT_DIR)/%.o, $(BOOT_SRCS_C))

DRIVER_SRCS_C := $(wildcard $(DRIVER_DIR)/*.c)
DRIVER_OBJS_C := $(patsubst $(DRIVER_DIR)/%.c, $(BUILD_DIR)/$(DRIVER_DIR)/%.o, $(DRIVER_SRCS_C))

.PHONY: all clean

all: | $(BUILD_DIR) $(BOOT_OBJS_S) $(BOOT_OBJS_C) $(DRIVER_OBJS_C) $(KERNEL_OBJS)

$(BUILD_DIR)/$(BOOT_DIR)/%.o: $(BOOT_DIR)/%.s
	$(AS) $< -o $@

$(BUILD_DIR)/$(BOOT_DIR)/%.o: $(BOOT_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(DRIVER_DIR)/%.o: $(DRIVER_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(KERNEL_DIR)/%.o: $(KERNEL_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/$(KERNEL_DIR)
	mkdir -p $(BUILD_DIR)/$(BOOT_DIR)
	mkdir -p $(BUILD_DIR)/$(DRIVER_DIR)

clean:
	rm -rf $(BUILD_DIR)
