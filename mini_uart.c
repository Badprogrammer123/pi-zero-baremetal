#include "mini_uart.h"
#include <string.h>

//default settings 


mini_data_set default_data_sett = {
	.size = AUX_MU_LCR_Data_8bit, 
	.data = "UART1_TX: SUCCESSFUL",
	.data_size = strlen("UART1_TX: SUCCESSFUL")  
};

set_mini_uart default_uart1_sett = {
        .baud_rate = AUX_UART1_DEFAULT_BAUD_RATE,
        .tx_enable = AUX_MU_CNTL_TX_ENABLE,
        .rx_enable = AUX_MU_CNTL_RX_ENABLE,
	.fifo_enable = 1,
	.data_settings = &default_data_sett

};



void uart1_puts(int char_count, volatile char *str ){
	int i = 0;
	while(char_count >= 0){
		if( ( AUX_BASE(AUX_MU_LSR_REG) & (1 << 5) ) != 0 ){
			AUX_BASE(AUX_MU_IO_REG) = str[i];
			i++;
			char_count --;
		}
	}	



}

void uart1_putc(volatile char character){
	while((AUX_BASE(AUX_MU_STAT_REG) & (1 << 0)) == 0);	
	AUX_BASE(AUX_MU_IO_REG) = character;
}

volatile char uart1_getc(){
	return AUX_BASE(AUX_MU_IO_REG);
}

set_mini_uart * uart1_init(set_mini_uart * mini_set){
        
	if(mini_set == NULL) mini_set = &default_uart1_sett;
	
	//Clear GPIO 14 and 15
        GPFSEL1 &= ~(GPIO14_CLEAR | GPIO15_CLEAR);
	
	//ALT5 GPIO 14 and 15 (RX_UART1 and TX_UART1) 
        GPFSEL1 |= GPIO14_TX_MODE ;
	GPFSEL1 |= GPIO15_RX_MODE ;
        

	//Enable UART1 required to access and configure registers
	AUX_BASE(AUX_ENABLE_REG) |= AUX_ENABLE_UART1;
        
	//Disable tx and rx to config
        AUX_BASE(AUX_MU_STAT_REG) &= AUX_MU_CNTL_RX_DISABLE & AUX_MU_CNTL_RX_DISABLE;
	
	//Baud Rate divisor
        AUX_BASE(AUX_MU_BAUD_REG) |= AUX_UART1_BAUD_DIVISOR(mini_set->baud_rate);


        //set data register size to 8 bits
        AUX_BASE(AUX_MU_LCR_REG) |= mini_set->data_settings->size;
	
	//Disable or Leave FIFO enabled
        AUX_BASE(AUX_MU_IIR_REG) &= mini_set->fifo_enable == 1 ? AUX_MU_IIR_FIFO_ENABLE : AUX_MU_IIR_FIFO_DISABLE;	
	/
	//Enable TX and RX interrupts
	AUX_BASE(AUX_MU_IER_REG) |= AUX_MU_IER_TX_INTERRUPT_ENABLE | AUX_MU_IER_RX_INTERRUPT_ENABLE; 


	//Re-enable RX or/and TX
        AUX_BASE(AUX_MU_CNTL_REG) |= mini_set->tx_enable | mini_set->rx_enable;


	return mini_set; 
}

void mini_uart_driver_setup(){
        set_mini_uart * mini_set = uart1_init(NULL);
	uart1_putc('a');
	

}


