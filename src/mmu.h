#ifndef mmu_h
#define mmu_h
// Protected mode descriptor table in 163 page
typedef struct {
        unsigned lim_15_0 : 16;  // Low bits of segment limit
        unsigned base_15_0 : 16; // Low bits of segment base address
        unsigned base_23_16 : 8; // Middle bits of segment base address
        unsigned type : 4;       // Segment type (see STS_ constants)
        unsigned s : 1;          // 0 = system, 1 = application
        unsigned dpl : 2;        // Descriptor Privilege Level
        unsigned p : 1;          // Present
        unsigned lim_19_16 : 4;  // High bits of segment limit
        unsigned avl : 1;        // Unused (available for software use)
        unsigned rsv1 : 1;       // Reserved
        unsigned db : 1;         // 0 = 16-bit segment, 1 = 32-bit segment
        unsigned g : 1;          // Granularity: limit scaled by 4K when set
        unsigned base_31_24 : 8; // High bits of segment base address
} DPS;
// 描述符表 48位
    typedef struct {
        unsigned limt : 16;  //GDT的大小。
        unsigned add_s : 32;  //GDT的起始位置。
    } GDT;
// 选择子
    typedef struct {        
        unsigned rpl : 2; //请求特权级
        unsigned ti : 1; // 0 for gdt, 1 for ldt
        unsigned index : 13; //index for DPS in memory
    } SL;

#define SEG(type, base, lim, dpl) (DPS){ \ 
            ((lim >> 12) & 0xffff), (unsigned)(base & 0xffff),\
            (unit)((base >> 16) & 0xff), type, 0, dpl, \ 
            1, (lim >> 28), 0, 0, 1, 1, (base >> 24)};
#define SEG16(type, base, lim, dpl) (DPS){ \ 
            ((lim >> 12) & 0xffff), (unsigned)(base & 0xffff),\
            (unit)((base >> 16) & 0xff), type, 0, dpl, \ 
            1, (lim >> 28), 0, 0, 1, 0, (base >> 24)};
#endif