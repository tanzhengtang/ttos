#include<stdio.h>
#include<stdlib.h>
#include"mmu.h" 
#include"dtyp.h"
// target: low 1 GB map to high 1GB
int main(){
    PDE p = PTDE(1,1,1,1,PDE_Phy_Adr);
}
