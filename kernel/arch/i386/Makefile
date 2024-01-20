BUILD_DIR := ../build/bootloader

BOOTLOADER_SRCS := $(wildcard *.s)
BOOTLOADER_OBJS := $(patsubst %.s, $(BUILD_DIR)/%.o, $(BOOTLOADER_SRCS))

AS := i686-elf-as

all: $(BOOTLOADER_OBJS)

$(BUILD_DIR)/%.o: %.s
	$(AS) $< -o $@

clean:
	rm $(BUILD_DIR)/*