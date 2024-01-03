#ifndef mmu_h
#define mmu_h
// 保护模式32位描述符 150page
    typedef struct {
        unsigned sb0 : 8; //base addr 31-24 bits
        unsigned g : 1; // 这个bit位等于1时，每一个段界限粒度大小为4字节。为0时为1字节。
        unsigned d : 1; // 为0表示指令中的有效地址和操作数为16位，为1则是32位。
        unsigned l : 1; // 1表示64位代码， 0 表示32位代码
        unsigned avl : 1; // available for use by systems programmers
        unsigned sl0 : 4; // segment limits 19-16
        unsigned p : 1; // 表示该段是否在实际的内存中存在。
        unsigned dpl : 2; //代码特权级。
        unsigned s : 1; //152 page. combine with type.
        unsigned type : 4; //153 page. combine with s.
        unsigned sb1 : 8; //base addr 23-16 bits
        unsigned sb2 : 16;  //base addr 15-0 bits
        unsigned sl1 : 16; // segment limits 15-0
    } DPS;
// 描述符表 48位
    typedef struct {
        unsigned add_s : 32;  //GDT的起始位置。
        unsigned limt : 16;  //GDT的大小。
    } GDT;
// 选择子
    typedef struct {
        unsigned index : 13; //index for DPS in memory
        unsigned ti : 1; // 0 for gdt, 1 for ldt
        unsigned rpl : 2; //请求特权级
    } SL;
#endif