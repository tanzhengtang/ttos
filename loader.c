#include "x86_intel.h"
void test(void){
    inb(0x92);
    oor(0x02);
    otb(0x92);
};