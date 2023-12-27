#ifndef mmu_h
#define mmu_h
// 保护模式32位描述符
    typedef struct {
        unsigned sb0 : 8; //base addr 31-24 bits
        unsigned g : 1; //gra
        unsigned d : 1; // unknown 
        unsigned l : 1; // unknown
        unsigned avl : 1; // available for use by systems programmers
        unsigned sl0 : 4; // segment limits 19-16
        unsigned p : 1; //segment present
        unsigned dpl : 2;
        unsigned s : 1;
        unsigned type : 4;
        unsigned sb1 : 8; //base addr 23-16 bits
        unsigned sb2 : 16;  //base addr 15-0 bits
        unsigned sl1 : 16; // segment limits 15-0
    } DPS;
// 描述符表 48位
    typedef struct {
        unsigned add_s : 32;
        unsigned limt : 16;
    } GDT;
// 选择子
    typedef struct {
        unsigned index : 13; //index for DPS in memory
        unsigned ti : 1; // 0 for gdt, 1 for ldt
        unsigned rpl : 2;
    } SL;
#endif