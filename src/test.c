#include<stdio.h>
#include"mmu.h"
int main(){
    short t = 0xfe13;
    char* c = (char *)&t;
    printf("%p\n", c);
    printf("%#x\n", *c);
    printf("%02x\n", *(++c));
    printf("%02x\n", *(++c));
}