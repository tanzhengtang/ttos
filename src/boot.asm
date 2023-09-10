%include "boot.inc"

start:
    cli
    cld

    xor ax,ax
    mov es,ax
    mov ds,ax
    mov ss,ax

A20Enable:
    call WaitInbufEmpty    ;2.等待8042 Input buffer为空；
    mov al, 0adh   ;向64h端口发送命令ADH(禁止键盘接口。Command Byte的bit-4被设置。当此命令被发布后，Keyboard将被禁止发送数据到Output Register。)
    mov dx, 64h
    out dx, al              ;3.发送禁止键盘操作命令
    call WaitInbufEmpty    ;4.等待8042 Input buffer为空；
    mov al, 0d0h
    mov dx, 64h
    out dx, al              ;5.发送读取8042 Output Port命令；
    call WaitOutbufFull     ;6.等待8042 Output buffer有数据；
    mov dx, 60h
    in al, dx               ;7.读取8042 Output buffer
    push ax                 ;保存读取的数据
    call WaitInbufEmpty     ;8.等待8042 Input buffer为空；
    mov al, 0d1h
    mov dx, 64h
    out dx, al              ;9.发送写 8042 Output Port命令
    call WaitInbufEmpty     ;10.等待8042 Input buffer为空
    pop ax
    or al, 02h              ;11.将从8042 Output Port得到的字节的bit 1置1
    mov dx, 60h
    out dx, al              ;写入Output Port
    call WaitInbufEmpty    ;12.等待8042 Input buffer为空
    mov al, 0aeh
    mov dx, 64h
    out dx, al              ;13.发送允许键盘操作命令

Pr_enable:
    lgdt [GDT_DES]
    mov eax, cr0  ;cr0寄存器32位，为控制寄存器。当它的第1位置1时，开启保护模式。
    or eax, CR0_PE
    mov cr0, eax
    
    jmp GDT_CODE - GDT - 1:Pat_Enable

Pat_Enable:
    xor ax, ax

WaitInbufEmpty:
            mov dx, 64h
            in al, dx               ;读取Status Register
            test al, 02h   ;测试第2bit是否为1，1表示还有数据在缓冲区
            jnz WaitInbufEmpty  ;zf=0，运算结果非0，即逻辑与为1
            ret

WaitOutbufFull:
            mov dx, 64h
            in al, dx
            test al, 01             ;读取Status Register
            jz WaitOutbufFull
            ret
  
GDT:
GDT_NULL:   dd 0,0
GDT_CODE:   Dtp GCD_DES, GCD_LIMIT, DR_32 + DR_CRW    
GDT_DATA:   Dtp GCD_DES, GCD_LIMIT, DR_32 + DR_DRW
    
GDT_DES:
dw GDT_DES - GDT - 1 ;size of gdt, why minus 1, becuase of null gdt.
dd GDT ;start address of gdt

%include "mbr_tail.inc"