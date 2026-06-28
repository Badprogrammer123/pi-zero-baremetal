#ifndef MINI_UART_H
#define MINI_UART_H



/* Base addresses */

#define AUX_BASE        0x3F215000
#define GPIO_BASE       0x3F200000
#define GPFSEL1 	0x3F200004

/* Mini UART register offsets */

#define AUX_ENABLE_REG  (0x04/4)
#define AUX_MU_IO_REG   (0x40/4)
#define AUX_MU_IER_REG  (0x44/4)
#define AUX_MU_IIR_REG  (0x48/4)
#define AUX_MU_LCR_REG  (0x4C/4)
#define AUX_MU_MCR_REG  (0x50/4)
#define AUX_MU_LSR_REG  (0x54/4)
#define AUX_MU_MSR_REG  (0x58/4)
#define AUX_MU_SCRATCH  (0x5C/4)
#define AUX_MU_CNTL_REG (0x60/4)
#define AUX_MU_STAT_REG (0x64/4)
#define AUX_MU_BAUD_REG (0x68/4)

/* GPIO PINS  */
#define GPIO14_TX_MODE		 (1 << 13) 
#define GPIO15_RX_MODE		 (1 << 16)
#define GPIO14_CLEAR		 (7 << 12) 
#define GPIO15_CLEAR 		 (7 << 15)

/* AUX UART1 ENABLE */
#define AUX_ENABLE_UART1	 (1 << 0)

/* TX and RX ENABLE */ 
#define AUX_MU_CNTL_RX_ENABLE	 (1 << 0)
#define AUX_MU_CNTL_TX_ENABLE 	 (1 << 1)

/* Mini UART IIR bits */
#define AUX_MU_IIR_CLEAR_RX_FIFO (1 << 1)
#define AUX_MU_IIR_CLEAR_TX_FIFO (1 << 2)
#define AUX_MU_IIR_FIFO_ENABLE   (1 << 0)
#define AUX_MU_IIR_FIFO_DISABLE  (3 << 6)

#endif

typedef struct mini_uart_data_settings {
	volatile unsigned int size; 

}mini_data_set;


typedef struct mini_uart_settings{
	unsigned int baud_rate;
	unsigned int tx_enable;
    unsigned int rx_enable;	
	unsigned fifo_disable; 
	struct mini_uart_data_settings *data_settings; 
}set_mini_uart;


void transmit_send(volatile unsigned int * uart_regs, int char_count, char *str ){
	int i = 0;
	while(char_count != 0){
		if( ((*(uart_regs + (AUX_MU_LSR_REG /4))) & (1 << 5)) != 0 ){
			*(uart_regs + (AUX_MU_IO_REG/4)) = str[i];
			i ++;
			char_count --;
		}
	}	



}


volatile unsigned int *set_uart(set_mini_uart * mini_set){
        //GPIO pins set to ALT5

        volatile unsigned int *uart_regs = (volatile unsigned int *) AUX_BASE;
        volatile unsigned int *set_pin_mode = (volatile unsigned int *) GPFSEL1;
        volatile unsigned int  baudrate = 250000000 / (8 * (mini_set->baud_rate + 1));
	
		//Clear GPIO 14 and 15
        *set_pin_mode &= ~(GPIO14_CLEAR | GPIO15_CLEAR);
	
		//ALT5 GPIO 14 and 15 (RX_UART1 and TX_UART1) 
        *set_pin_mode |= GPIO14_TX_MODE ;
        *set_pin_mode |= GPIO15_RX_MODE ;
        

		//Enable UART1 required to access and configure registers
		*(uart_regs + AUX_ENABLE_REG) |= AUX_ENABLE_UART1;
        
		//Disable tx and rx to config
        *(uart_regs + AUX_MU_STAT_REG) &= ~(AUX_MU_CNTL_RX_ENABLE  | AUX_MU_CNTL_RX_ENABLE );
	
        *(uart_regs) |= baudrate;


        //set data register size to 8 bits
        *(uart_regs + AUX_MU_LCR_REG) |= mini_set->data_settings->size;
	

        *(uart_regs + AUX_MU_IIR_REG) &= mini_set->fifo_disable == 0 ? AUX_MU_IIR_FIFO_ENABLE : ~(AUX_MU_IIR_FIFO_DISABLE);
	
		*(uart_regs + AUX_MU_IIR_REG) |= mini_set->fifo_disable == 0 ? AUX_MU_IIR_CLEAR_TX_FIFO | AUX_MU_IIR_CLEAR_RX_FIFO : 0; 

        *(uart_regs + AUX_MU_CNTL_REG) |= mini_set->tx_enable | mini_set->rx_enable;

	return uart_regs; 
	
}


