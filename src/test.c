#include<stdio.h>
#include"mmu.h" 
// target: low 1 GB map to high 1GB
typedef struct 
{
    unsigned d : 1;
    /* data */
}PT;

int main(){
    PT* p = (PT *)(0x100000);
    *p = (PT){1};
    printf("%d", p->d);
    return 1;
}