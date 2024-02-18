%include "boot.inc"
global start 
extern readmain
extern pat_set

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
    
    jmp dword KCODE<<3:Pat_Enable ; Page 172 - 173. 


BITS 32
Pat_Enable:
    xor eax, eax
    mov eax, KDATA<<3
    mov ds, eax
    mov ss, eax
    mov es, eax 
    mov esp, start

bootc:
    call readmain

spin:
    jmp  spin