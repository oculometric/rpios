rm *.o
rm kernel8.img


aarch64-elf-as -c boot.s -o boot.o

aarch64-elf-gcc -ffreestanding -c kernel.c -o kernel.o -O2 -Wall -Wextra
aarch64-elf-gcc -ffreestanding -c mmio.c -o mmio.o -O2 -Wall -Wextra
aarch64-elf-gcc -ffreestanding -c uart.c -o uart.o -O2 -Wall -Wextra
aarch64-elf-gcc -ffreestanding -c util.c -o util.o -O2 -Wall -Wextra
aarch64-elf-gcc -ffreestanding -c gui.c -o gui.o -O2 -Wall -Wextra
aarch64-elf-gcc -ffreestanding -c mem.c -o mem.o -O2 -Wall -Wextra

aarch64-elf-gcc -T linker.ld -o rpios.elf -ffreestanding -O2 -nostdlib *.o -lgcc

aarch64-elf-objcopy rpios.elf -O binary kernel8.img