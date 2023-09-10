gdt_code:
dw 0xffff
dw 0
dw 0
db 10011010b
db 11001111b
db 0
gdt_sd:
dw 0xffff
dw 0
dw 0
db 10010010b
db 11001111b
db 0
gdt_e:

gdt_des:
dw gdt_e - gdt_sd - 1 ;size of gdt, why minus 1, becuase of null gdt.
dd gdt_sd ;start address of gdt