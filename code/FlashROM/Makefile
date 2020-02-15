
all: ROM.bin

ROM.bin:	main.o
	arm-none-eabi-ld main.o -o main.elf -T link.ld
	arm-none-eabi-objcopy -O binary main.elf main.bin

main.o: 	main.c
	arm-none-eabi-gcc -mcpu=cortex-m0plus -std=c99 -mthumb main.c -c

