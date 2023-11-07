CC = gcc
ASFLAGS = -masm="intel" -gdwarf-2 -Wa
CFLAGS = -masm="intel" -fno-pic -static -fno-builtin -fno-strict-aliasing -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer -g
t: t.o
