CFLAGS = -fno-pie -no-pie -fno-pic -static -fno-builtin -fno-strict-aliasing  -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer -O2 -march=i386 -masm=intel -fno-pic -nostdinc

a: t1.c t1s.o
	gcc $(CFLAGS) t1.c -o t1c.o
	ld -melf_i386 t1s.o t1c.o -o a -e _start

t1s.o: t1.asm
	nasm -felf32 t1.asm -o t1s.o

.PRECIOUS: 
QEMU = qemu-system-i386

QEMUOPTS = -drive file=tt.img,index=0,media=disk,format=raw -smp 2 -m 512
GDBPORT = $(shell expr `id -u` % 5000 + 25000)

QEMUGDB = $(shell if $(QEMU) -help | grep -q '^-gdb';then echo "-gdb tcp::$(GDBPORT)";else echo "-s -p $(GDBPORT)"; fi)

qemu-nox-gdb: tt.img sign
	$(QEMU) -nographic $(QEMUOPTS) -S $(QEMUGDB)

tt.img: tt.asm
	nasm -fbin tt.asm -o tt.img
	./sign tt.img

sign: sign.c
	gcc sign.c -o sign

$(info SOURCES variable is: $(QEMUGDB))

.PHONY: clean
clean:
	-rm *.o 

t1.img: t1s.o t1c.o
	ld -N -Ttext 0x7c00 -melf_i386 t1s.o t1c.o -o t1 -e _start
	objcopy -S -O binary -j .text t1 t1.img
	../sign t1.img