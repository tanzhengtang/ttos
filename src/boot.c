#include"x86_intel.h"
#include"rgpt.h"
#include"mmu.h"
#include"elf.h"
// init address is 0.

#define DISK_SECTOR_NUMS 0x01
#define DISK_START_ADDRESS 0x0000000
#define KERNEL_DISK_START_ADDRESS DISK_START_ADDRESS + 1
#define KERNEL_MEM_ADDRESS 0x9000
#define KERNEL_SIZE 1024

u16 wait_disk(void){
   u16 res = inb((u16)DISK_PORT_STATUS);
   return res & DISK_SM_BSY;
};

void readsec(u16* ma, u16 da){
   u8 c = 0;
   otb(1,(u16)DISK_PORT_SC);
   otb((u16)da,(u16)DISK_PORT_LBA_LOW); // write in start disk sector.
   otb(da >> 8,(u16)DISK_PORT_LBA_MID);
   otb(da >> 8,(u16)DISK_PORT_LBA_HIGH);
   otb((da >> 4) | DISK_DEVICE_LBA_CODE,(u16)DISK_PORT_DEVICE);
   otb((u16)DISK_PORT_STATUS, (u16)DISK_READ_DATA);
   while (!wait_disk())
   {
      *(ma + 2*c) = inb(DISK_PORT_DATA);
      c++;
      if(c == 256){
         break;
      }
   }
};

void readseg(u16* ma, u16 da, u16 byte)
{
   u16* ema = ma + byte;
   for (; ma < ema; da++)
   {
      readsec(ma, da);
      ma = ma + DISK_SIZE;
   }
   return ;
};

void readmain(){
   Elf32_Ehdr * em = PDE_Phy_Adr;
   readsec((u16 *)em, KERNEL_DISK_START_ADDRESS);
   while (!wait_disk());
   if(em->e_ident[0] != 0x7f){
      return;
   }
   
   readseg((u16 *)KERNEL_MEM_ADDRESS, (u16)KERNEL_DISK_START_ADDRESS, (u16)KERNEL_SIZE);
   return ;
};

void pat_set(){
   // init first phy 1 MB to vdr 0xc0000000
   PDE* p = (PDE*)(PDE_Phy_Adr + 4 * (KVDR >> 22));
   PDE* pt;
   *p = PTDE(1, 1, 1, 0, PDE_Phy_Adr + 1024 * 4);
   for (int i = 0; i < 256; i++)
   {
      pt = (PDE*)(PTE_Phy_Adr + i * 4);
      *pt = PTDE(1, 1, 1, 0, i * 4096);
   }
   // for pde self 0xc0100000 vdr
   pt = (PDE*)(PTE_Phy_Adr + ((PDE_Phy_Adr >> 12) * 4 ));
   *pt = PTDE(1, 1, 1, 0, PDE_Phy_Adr);

   // for 1MB kernel 0xc0500000 vdr
   p = (PDE*)(PDE_Phy_Adr + 4 * (KVDR_CODE >> 22));
   for (int i = 0; i < 256; i++)
   {
      pt = (PDE*)(PDVR_CODE + 1024 * 4 + i * 4);
      *pt = PTDE(1, 1, 1, 0, i * 4096);
   }
   asm volatile(
      "mov eax, 0x00100000;"
      "mov cr3, eax;"
      "mov eax, cr0;"
      "or eax, 0x80000000;"
      "mov cr0, eax;"
   );
   return;
}