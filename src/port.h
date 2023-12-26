#ifndef port_h
#define port_h
/*
内存布局表:65页
通用寄存器:88页
标志寄存器:110页 & 条件转移指令 112页
硬盘端口:138页
*/
#define DISK_PORT_DATA 0x170 
#define DISK_PORT_EF 0x171
#define DISK_PORT_SC 0x172
// LBA访问硬盘有28位和48位，目前使用的是28位。专用的LBA端口只有24位，剩余4位在device寄存器的低4位中。
#define DISK_PORT_LBA_LOW 0x173 //8bits for low.  0-7
#define DISK_PORT_LBA_MID 0x174 //8bits for mid. 8-15
#define DISK_PORT_LBA_HIGH 0x175 //8bits for high. 16-23
#define DISK_PORT_DEVICE 0x176 //0-3 for LBA's 24-27. 第 4 位用来指定通道上的主盘或从盘，0 代表主盘，1 代 表从盘。第 6 位用来设置是否启用 LBA 方式，1 代表启用 LBA 模式，0 代表启用 CHS 模式。另外的两位: 第 5 位和第 7 位是固定为 1 的，称为 MBS 位，不用关注.
#define DISK_PORT_STATUS 0x177 //读的时候是状态机，写的时候是command
// 只需1个扇区，起始位置是0
#define DISK_SECTOR_NUMS 0x01
#define DISK_ADDRESS 0x0000000

#define DISK_DEVICE_LBA_CODE 0b11100000 //开启LBA的DEVICE代码 140页详情.
//command of disk port for status register
#define DISK_IDENTIFY 0xEC
#define DISK_READ_DATA 0x20
#define DISK_WRITE_DATA 0x30

#define DISK_SM_BSY 0b10000000 //表示硬盘正忙，勿扰
#define DISK_SM_DRDY 0b01000000 //表示设备就绪，等待指令,对硬盘诊断鉴别时候用的，表示硬盘检测正常
#define DISK_SM_DRQ 0b00000100 //表示硬盘已经准备好数据，随时可以输出
#define DISK_SM_ERR 0b00000001 //表示有错误发生，错误信息见error寄存器

#endif