// #include<stdio.h>
#include"mmu.h" 
#define KERNEL_BASE_ADDR 
// target: low 1 GB map to high 1GB
int main(){
    int * a = (int *)(0x100000);
    *a = 1;
    return 1;
}