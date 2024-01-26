#include"x86_intel.h"
#include"rgpt.h"
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
   otb((u16)DISK_START_ADDRESS,(u16)DISK_PORT_LBA_LOW); // write in start disk sector.
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
   readseg((u16 *)KERNEL_DISK_START_ADDRESS, (u16)KERNEL_MEM_ADDRESS, (u16)KERNEL_SIZE);
   return ;
}

void pat_set(){
   
   return ;
}