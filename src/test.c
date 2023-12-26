#include"x86_intel.h"
#include"port.h"

int main(int argc, char const *argv[])
{
   otb((u16)DISK_SECTOR_NUMS,(u16)DISK_PORT_SC); // 写入要读几个扇区.
   otb((u16)DISK_ADDRESS,(u16)DISK_PORT_LBA_LOW); // 写入扇区起始地址
   otb((u16)(DISK_ADDRESS >> 8),(u16)DISK_PORT_LBA_MID);
   otb((u16)(DISK_ADDRESS >> 8),(u16)DISK_PORT_LBA_HIGH);
   otb((u16)((DISK_ADDRESS >> 4) | DISK_DEVICE_LBA_CODE),(u16)DISK_PORT_DEVICE);
   otb((u16)(DISK_IDENTIFY),DISK_PORT_STATUS); //进行硬盘识别
   u16 res = inb((u16)DISK_PORT_STATUS);//返回操作情况
   if(res )
   //待续，需要写一下掩码来判断status返回的结果。
   return 0;
}
