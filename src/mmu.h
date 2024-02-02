#ifndef mmu_h
#define mmu_h
// Protected mode about descriptor table in 163 page
// descriptor seg
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
// descriptor table 48 bits
    typedef struct {
        unsigned limt : 16;  //GDT size。
        unsigned add_s : 32;  //descriptor seg init address。
    } GDT;
// selector 16 bits
    typedef struct {        
        unsigned rpl : 2; //Privilege
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


// Page Table Entry & Page Dir Entry Page 207
typedef struct 
{
    unsigned p : 1; 
    unsigned rw : 1;
    unsigned us : 1;
    unsigned pwt : 1;
    unsigned pcd : 1;
    unsigned a : 1;
    unsigned r : 1; // Reserved
    unsigned ps : 1; // 0 indicates 4KB.
    unsigned g : 1;
    unsigned avl : 3;
    unsigned addr : 20;
} PDE;

typedef struct 
{
    unsigned p : 1; 
    unsigned rw : 1;
    unsigned us : 1;
    unsigned pwt : 1;
    unsigned pcd : 1;
    unsigned a : 1;
    unsigned d : 1; // dirty 
    unsigned pat : 1; 
    unsigned g : 1;
    unsigned avl : 3;
    unsigned addr : 20;
} PTE;

#define PG_P 0b1 
#define PG_RW_R 0
#define PG_RW_W 0b1
#define PG_US_S 0
#define PG_US_U 0b1

#define PTDE(p, rw, us, avl, addr) (PDE){\
    0, rw, us, 0, 0, 0, 0, 0, 0, \
    avl, addr \
};

typedef struct
{   
    unsigned r1 : 3; // Reserved
    unsigned pwt : 1;
    unsigned pcd : 1;
    unsigned r2 : 7; // Reserved
    unsigned pdr : 20; //PDE address 12-32 bits.
} CR3;

// Control Register flags
#define CR0_PE 0x00000001 //start protect mode
#define CR0_PG 0x80000000 //start page mode
#define CR0_WP 0x00010000 //start write protect mode

#define NPDENTRIES      1024    // # directory entries per page directory
#define NPTENTRIES      1024    // # PTEs per page table

#define PDE_Phy_Adr 0x00100000 //PDE Start Physical Address
#define PTE_Phy_Adr (PDE_Phy_Adr + NPDENTRIES*4)  
#define PTE_Phy_End_Adr (PTE_Phy_Adr + (NPDENTRIES*NPTENTRIES*4))


#endif