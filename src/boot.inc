;org 0x7c00
;如果是8086（20位机器），那么必定只能寻址1MB(2^20)。
;此时的内存空间为:

BIOS_ROM_START equ 0x000F0000 ;BIOS ROM (960KB) -> end at 0x000FFFFF

DEVICE_ROM_START equ 0x000C0000 ; 16-bit devices,expansion ROMs (768KB) -> end at 0x000EFFFF

VGS_DISPLAY_START equ 0x000A0000 ; VGA Display (64KB) -> end at 0x000BFFFF

FREE_MEM_START equ 0x00000000; FREE USED MEM -> end at 0x0009FFFF
; 此时低位的地址为 0x00000000 - 0x0009FFFF 为暂时空置的内存空间。 因此上面0x000A0000 - 0x00100000 在所有intel的机器上都有这么一个内存黑洞，后面容量更大的cpu为了兼容旧代的cpu。

MBR_START equ 0x00007c00;

CR0_PE equ 0x00000001; protection enable

; Descriptor definiton is divided into three section.
; %1 for address base 32 bits
; %2 for limit of mem 20bits
; %3 for all attr of descriptor 12bits
%macro Dtp 3 
    dw (%2 & 0x0ffff) ; 0 - 15 for 0 - 15 of limit bits
    dw (%1 & 0x0000ffff); 16 - 31 for 0 - 15 of address base bits
    db ((%1 >> 16) & 0x000000ff); 32 - 39 for 16 - 24 of address bits
    db (%3 & 0x0ff) ; 39 - 47 for first 8 bits of attr
    db (%2 >> 16) | (( 0xf00 & %3 ) >> 4) ; 48 - 55 bits, first 4 bits for the limit bits and second 4 bits for the attr bits.
    db (%1 >> 24) ; 56 - 63 for the last 8 bits for address base
%endmacro
;
GCD_DES equ 0
GCD_LIMIT equ 0xfffff

DR_32 equ 0xc00 ; 1100B G,D/B,L,AVL
DR_CRW equ 0x9a ; 10011010B 代码段 TYPE(4),S(1),DPL(2),P(1)
DR_DRW equ 0x92 ; 10010010B 数据段 TYPE(4),S(1),DPL(2),P(1)