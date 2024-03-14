# C  
## Inline Assembly Language in C Code  
- Quick Read: https://www.codeproject.com/Articles/15971/Using-Inline-Assembly-in-C-C  
- Normal Read: https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html  
- Manual: https://gcc.gnu.org/onlinedocs/gcc/Using-Assembly-Language-with-C.html  

## Check Normal Segment in Obj File  
- https://blog.csdn.net/qq_42570601/article/details/127360128  

# Nasm  
调用C中的变量：https://www.onekbase.com/blog/os/mkos/nasmcvar/  
必须使用[变量名]进行，若想传入某个变量的地址一般使用另外的虚指针保存后，传入虚指针进行。
例如：
```
// In C
extern void *pt;
extern u16 pdt[];
u16 pdt[2] = {[0] = 1, [1] = 2};
void *pt = (void*)pdt;
// In asm 
extern pt
global et
et:
    mov ax, [pt]
```  
此时pt传入的便是pdt的地址。