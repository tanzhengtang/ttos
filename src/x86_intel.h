#ifndef x86_intel_h
#define x86_intel_h
#include "dtyp.h"

static inline u16 inb(u16 port){
	u16 data;
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
};


#endif