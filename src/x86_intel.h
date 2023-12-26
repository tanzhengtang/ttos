#ifndef x86_intel_h
#define x86_intel_h
#include "dtyp.h"

static inline u16 inb(u16 port){
	u16 data = -1;
	asm volatile(
		"in %0,%1"
		:"=a"(data) :"d"(port):);
	return data;
};

static inline void otb(u16 data,u16 port){
	asm volatile(
		"out %1,%0"
		::"a"(data),"d"(port):);
	return;
}

/* static inline void oor(u8 num){
	__asm__ __volatile__(
		"or %al, %0"
		::"r"(num):);
	return;
}
*/
// static inline void inw(){
// 	__asm__ __volatile__(""
// 	: : :);
// 	return;
// };

#endif