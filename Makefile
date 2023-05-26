H_FILES = src/h

SRC = src
OUT = build

C_SRC = $(SRC)/c
C_OUT = $(OUT)/o/c

S_SRC = $(SRC)/s
S_OUT = $(OUT)/o/s

C_FILES_I := $(wildcard $(C_SRC)/*.c)
C_FILES_O := $(patsubst $(C_SRC)/%.c, $(C_OUT)/%.o, $(C_FILES_I))

S_FILES_I := $(wildcard $(S_SRC)/*.s)
S_FILES_O := $(patsubst $(S_SRC)/%.s, $(S_OUT)/%.o, $(S_FILES_I))

LINKER_DOCUMENT = $(SRC)/linker.ld

ELF_O = $(OUT)/rpios.elf

KERNEL8 = kernel8.img
KERNEL8_O = $(OUT)/$(KERNEL8)

DISK_DIR = disk
DISK_FIRMWARE_DIR = firmware
DISK_FIRMWARE := bootcode.bin fixup.dat start.elf
DISK_FIRMWARE_I := $(patsubst %, $(DISK_FIRMWARE_DIR)/%, $(DISK_FIRMWARE))

all: build

clean:
	rm -r $(OUT)
	rm -r $(DISK_DIR)

setup:
	mkdir -p $(C_OUT)
	mkdir -p $(S_OUT)

$(C_OUT)/%.o: $(C_SRC)/%.c $(H_FILES) setup
	aarch64-elf-gcc -ffreestanding -I$(H_FILES) -c $< -o $@ -O2 -Wall -Wextra

$(S_OUT)/%.o: $(S_SRC)/%.s setup
	aarch64-elf-as -c $< -o $@

build: $(C_FILES_O) $(S_FILES_O)
	aarch64-elf-gcc -T $(LINKER_DOCUMENT) -o $(ELF_O) -ffreestanding -O2 -nostdlib $(C_FILES_O) $(S_FILES_O) -lgcc
	aarch64-elf-objcopy $(ELF_O) -O binary $(KERNEL8_O)

present: build
	cp $(KERNEL8_O) $(KERNEL8)

run: build
	qemu-system-aarch64 -M raspi3b -serial stdio -kernel $(KERNEL8_O)

disk: build
	mkdir -p $(DISK_DIR)
	cp $(DISK_FIRMWARE_I) $(DISK_DIR)
	cp $(KERNEL8_O) $(DISK_DIR)

