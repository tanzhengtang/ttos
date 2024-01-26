%include "boot.inc"
global start 
extern readmain

BITS 16
start:
    cli
    cld

    xor ax,ax
    mov es,ax
    mov ds,ax
    mov ss,ax

enable_a20:
    wait_for_kbd_ready:
        in al, 0x64       
        test al, 2        
        jnz wait_for_kbd_ready  
    mov al, 0xd1        
    out 0x64, al        
    wait_for_kbd_ready_2:
        in al, 0x64     
        test al, 2       
        jnz wait_for_kbd_ready_2 
    mov al, 0xdf       
    out 0x60, al        

Pr_enable:
    lgdt [GDT_DES]
    mov eax, cr0  ;cr0寄存器32位，为控制寄存器。当它的第1位置1时，开启保护模式。
    or eax, CR0_PE
    mov cr0, eax
    
    jmp dword GDT_CODE - GDT - 1:Pat_Enable ; Page 172 - 173. 


BITS 32
Pat_Enable:
    xor eax, eax

bootc:
    call readmain

GDT:
GDT_NULL:   dd 0,0
GDT_CODE:   Dtp GCD_DES, GCD_LIMIT, DR_32 + DR_CRW    
GDT_DATA:   Dtp GCD_DES, GCD_LIMIT, DR_32 + DR_DRW
    
GDT_DES:
dw GDT_DES - GDT - 1 ;size of gdt, why minus 1, becuase of null gdt.
dd GDT ;start address of gdt