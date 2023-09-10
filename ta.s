;global _main
;extern _pri

;_main:
;mov ax,0x1
;call _pri

;times 510 - ($ - $$) db 0 
;db 0x55,0xAA
db (0x5555 >> 16)
db (0x5555 >> 8)