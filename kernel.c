#include "mini_uart.h"
#include <string.h>





set_mini_uart test = {
	.baud_rate = 115200,
	.tx_enable = AUX_MU_CNTL_TX_ENABLE,
	.rx_enable = AUX_MU_CNTL_RX_ENABLE ,	
};



void kernel_main(){
	mini_data_set data;
	test.data_settings = &data;
       	test.data_settings->size = 1; 
	volatile unsigned int *regs = set_uart(&test); 
	transmit_send(regs, strlen("hello my name is florant"), "hello my name is florant"); 



}
