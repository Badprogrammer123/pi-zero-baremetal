#include <stdio.h>
#include "interrupts.h"
#include "mini_uart.h"

void kernel_main(){
	mini_uart_driver_setup();
	interrupt_enable();	
}	
