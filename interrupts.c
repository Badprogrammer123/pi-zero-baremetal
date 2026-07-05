#include <stdio.h>
#include "mini_uart.h"
#include "interrupts.h"

void interrupt_enable() {
	volatile unsigned int reg; 
	asm volatile("MRC p15, 0, %0, c12, c12, 5" : "=r" (reg));
	reg |= (1 << 0);  
	asm volatile("MCR p15, 0, %0, c12, c12, 5" :: "r"(reg));
	asm volatile("MRC p15, 0, %0, c12, c12, 7" : "=r"(reg)); 
	reg |= (1 << 0); 
	asm volatile ("MCR p15, 0, %0, c12, c12, 7" :: "r" (reg));
	asm volatile("LDR R0, =__vector_base_table_start");
	asm volatile("MCR p15, 0, R0, c12, c0, 0"); 
	asm volatile("MRC p15, 0, %0, c12, c1, 1" : "=r" (reg));
	uart1_putc((reg & (1 << 7)) + '0');
	asm volatile("MRC p15, 0, %0 ,c12, c12, 4" : "=r" (reg)); 
	reg |= (1 << 0);
	asm volatile("MCR p15, 0, %0, c12, c12, 4" :: "r" (reg));
	uart1_putc((AUX_BASE((AUX_MU_IIR_REG)) >> 1) & (~31));
}	
 
