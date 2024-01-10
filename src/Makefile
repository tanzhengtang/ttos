CFLAGS = -fno-pie -fno-pic -static -fno-builtin -fno-strict-aliasing  -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer -O2 -march=i386 -masm=intel -fno-pic -nostdinc
CC = i386-jos-elf-gcc
LD = i386-jos-elf-ld
LFLAGS = -m elf_i386
OBJCOPY = 

ttos.img: bootblock kernel
	dd if=/dev/zero of=ttos.img count=10000
	dd if=bootblock of=ttos.img conv=notrunc
	dd if=kernel of=ttos.img seek=1 conv=notrunc  

bootblock: boot.c boot.asm sign
	nasm -M -g -felf32 boot.asm -o boota.o 
	$(CC) $(CFLAGS) -c boot.c -o bootc.o
	$(LD) $(LFLAGS) -N -e start -Ttext 0x7c00 boota.o bootc.o -o bootblock.o 
	$(OBJCOPY) -S -O binary -j .text bootblock.o bootblock
	./sign bootblock

kernel: 
	echo 1111 > kernel

sign: sign.c
	gcc sign.c -o sign	

.PRECIOUS: 
QEMU = qemu-system-i386

QEMUOPTS = -drive file=ttos.img,index=0,media=disk,format=raw -smp 2 -m 512
GDBPORT = $(shell expr `id -u` % 5000 + 25000)

QEMUGDB = $(shell if $(QEMU) -help | grep -q '^-gdb';then echo "-gdb tcp::$(GDBPORT)";else echo "-s -p $(GDBPORT)"; fi)

qemu-nox-gdb: ttos.img sign
	$(QEMU) -nographic $(QEMUOPTS) -S $(QEMUGDB)

$(info SOURCES variable is: $(QEMUGDB))

.PHONY: clean
clean:
	-rm *.o 

t1.img: t1s.o t1c.o
	ld -N -Ttext 0x7c00 -melf_i386 t1s.o t1c.o -o t1 -e _start
	objcopy -S -O binary -j .text t1 t1.img
	../sign t1.img