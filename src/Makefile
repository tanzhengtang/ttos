ifndef TOOLPREFIX
TOOLPREFIX := $(shell if i386-jos-elf-objdump -i 2>&1 | grep '^elf32-i386$$' >/dev/null 2>&1; \
	then echo 'i386-jos-elf-'; \
	elif objdump -i 2>&1 | grep 'elf32-i386' >/dev/null 2>&1; \
	then echo ''; \
	else echo "***" 1>&2; \
	echo "*** Error: Couldn't find an i386-*-elf version of GCC/binutils." 1>&2; \
	echo "*** Is the directory with i386-jos-elf-gcc in your PATH?" 1>&2; \
	echo "*** If your i386-*-elf toolchain is installed with a command" 1>&2; \
	echo "*** prefix other than 'i386-jos-elf-', set your TOOLPREFIX" 1>&2; \
	echo "*** environment variable to that prefix and run 'make' again." 1>&2; \
	echo "*** To turn off this error, run 'gmake TOOLPREFIX= ...'." 1>&2; \
	echo "***" 1>&2; exit 1; fi)
endif

ifndef QEMU
QEMU = $(shell if which qemu > /dev/null; \
	then echo qemu; exit; \
	elif which qemu-system-i386 > /dev/null; \
	then echo qemu-system-i386; exit; \
	elif which qemu-system-x86_64 > /dev/null; \
	then echo qemu-system-x86_64; exit; \
	else \
	qemu=/Applications/Q.app/Contents/MacOS/i386-softmmu.app/Contents/MacOS/i386-softmmu; \
	if test -x $$qemu; then echo $$qemu; exit; fi; fi; \
	echo "***" 1>&2; \
	echo "*** Error: Couldn't find a working QEMU executable." 1>&2; \
	echo "*** Is the directory containing the qemu binary in your PATH" 1>&2; \
	echo "*** or have you tried setting the QEMU variable in Makefile?" 1>&2; \
	echo "***" 1>&2; exit 1)
endif

CFLAGS = -fno-pie -fno-pic -static -fno-builtin -fno-strict-aliasing  -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer -O2 -march=i386 -masm=intel -fno-pic -nostdinc
CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)gas
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy
OBJDUMP = $(TOOLPREFIX)objdump
LFLAGS = -m elf_i386

ttos.img: bootblock kernel
	dd if=/dev/zero of=ttos.img count=10000
	dd if=bootblock of=ttos.img conv=notrunc
	dd if=kernel of=ttos.img seek=1 conv=notrunc  

bootblock: boot.c boot.asm sign
	nasm -g -felf32 boot.asm -o boota.o 
	$(CC) $(CFLAGS) -c boot.c -o bootc.o
	$(LD) $(LFLAGS) -N -e start -Ttext 0x7c00 boota.o bootc.o -o bootblock.o 
	$(OBJCOPY) -S -O binary -j .text bootblock.o bootblock
	./sign bootblock

kernel: 
	@echo 1111 > kernel

sign: sign.c
	gcc sign.c -o sign	

.PRECIOUS: 
QEMU = qemu-system-i386

QEMUOPTS = -drive file=ttos.img,index=0,media=disk,format=raw -smp 2 -m 512
GDBPORT = $(shell expr `id -u` % 5000 + 25000)

QEMUGDB = $(shell if $(QEMU) -help | grep -q '^-gdb';then echo "-gdb tcp::$(GDBPORT)";else echo "-s -p $(GDBPORT)"; fi)

qemu-nox-gdb: ttos.img
	$(QEMU) -nographic $(QEMUOPTS) -S $(QEMUGDB)

$(info SOURCES variable is: $(QEMUGDB))

.PHONY: clean
clean:
	-rm *.o 