# The Main Ref  
## Xv6 and Mit 6.828 
- https://pdos.csail.mit.edu/6.828/2017  

# 软件环境设置  
## GDB及GCC安装  
- Mac: https://www.cnblogs.com/booturbo/archive/2023/05/09/17384509.html && install binutils for elf headers -> https://www.jianshu.com/p/4b93b0665a2b

## QEMU安装  
- Mac: brew install qemu  

## NASM安装  
- Mac: brew install nasm  

## Mac Note. 
* 对Mac下的交叉编译折腾了比较长的时间，似乎没有特定的库安装，可以使得gcc-13可以进行其他平台的编译，而是安装其他的编译器到mac下来进行编译。如进行jos-i386的编译，那么我们需要安装i386-jos-gcc到mac上。以6.828的交叉编译为例子: https://pdos.csail.mit.edu/6.828/2017/tools.html#chain.  