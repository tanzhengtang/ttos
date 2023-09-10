#ifndef x86_intel_h
#define x86_intel_h
#include "dtyp.h"
// static inline void mv16(){
//   __asm__ __volatile__(
// 	"mov "
// );
// 	return;
// };

// static inline void it(){
//   __asm__ __volatile__(
// 	"int %0"
// 	:
// 	:
// 	:
//  );
// 	return;
// };

static inline void inb(u8 port){
	__asm__ __volatile__(
		"in %al,%0"
		: :"r"(port):);
	return;
};

static inline void otb(u8 port){
	__asm__ __volatile__(
		"out %0,%al"
		: :"r"(port):);
	return;
}

static inline void oor(u8 num){
	__asm__ __volatile__(
		"or %al, %0"
		::"r"(num):);
	return;
}

// static inline void inw(){
// 	__asm__ __volatile__(""
// 	: : :);
// 	return;
// };

#endif