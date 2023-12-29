#include"x86_intel.h"
#include"rgpt.h"
// 只需1个扇区，起始位置是0
#define DISK_SECTOR_NUMS 0x01
#define DISK_ADDRESS 0x0000000
u16 wait_disk(void){
   u16 res = inb((u16)DISK_PORT_STATUS);
   return res & DISK_SM_BSY;
}
void Rdata_disk(u16 sec_num, u16 disk_addr, u16* mem_addr){
   u8 c = 0;
   otb(sec_num,(u16)DISK_PORT_SC);
   otb((u16)DISK_ADDRESS,(u16)DISK_PORT_LBA_LOW); // 写入扇区起始地址
   otb(disk_addr >> 8,(u16)DISK_PORT_LBA_MID);
   otb(disk_addr>> 8,(u16)DISK_PORT_LBA_HIGH);
   otb((disk_addr >> 4) | DISK_DEVICE_LBA_CODE,(u16)DISK_PORT_DEVICE);
   while (!wait_disk())
   {
      *(mem_addr + c) = inb(DISK_PORT_DATA);
      c++;
      if( c == 255){
         break;
      }
   }
}

void disk_main()
{
   Rdata_disk((u16)(0x1), (u16)(0x0), (u16*)(0x7c00));
   return ;
}
