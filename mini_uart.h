#include <stddef.h>
#include "gpio.h"


#ifndef MINI_UART_H

#define MINI_UART_H


/* Base AUX address */

#define AUX_BASE(offset)      (*(volatile unsigned int *) (0x3F215000 + offset))

/* Mini UART register offsets */

#define AUX_ENABLE_REG  0x04
#define AUX_MU_IO_REG   0x40
#define AUX_MU_IER_REG  0x44
#define AUX_MU_IIR_REG  0x48
#define AUX_MU_LCR_REG  0x4C
#define AUX_MU_MCR_REG  0x50
#define AUX_MU_LSR_REG  0x54
#define AUX_MU_MSR_REG 	0x58
#define AUX_MU_SCRATCH  0x5C
#define AUX_MU_CNTL_REG 0x60
#define AUX_MU_STAT_REG 0x64
#define AUX_MU_BAUD_REG 0x68

/* GPIO PINS  */
#define GPIO14_TX_MODE		 (1 << 13) 
#define GPIO15_RX_MODE		 (1 << 16)
#define GPIO14_CLEAR		 (7 << 12) 
#define GPIO15_CLEAR 		 (7 << 15)

/* AUX UART1 ENABLE */
#define AUX_ENABLE_UART1	 (1 << 0)

/* Mini UART LCR bits */ 
#define AUX_MU_LCR_Data_8bit	 (3 << 0)
#define AUX_MU_LCR_Data_7bit    ~(3 << 0) // BCM2835 defines data size default to be 7bit but for this driver we will be using 8bit defined in the macro on top

/* Mini UART CNTL bit */ 
#define AUX_MU_CNTL_RX_ENABLE	 (1 << 0)
#define AUX_MU_CNTL_TX_ENABLE 	 (1 << 1)
#define AUX_MU_CNTL_RX_DISABLE	~(1 << 0)
#define AUX_MU_CNTL_TX_DISABLE	~(1 << 1)


/* Mini UART IIR bits */
#define AUX_MU_IIR_CLEAR_RX_FIFO  (1 << 1) //Clear FIFO receive symbols
#define AUX_MU_IIR_CLEAR_TX_FIFO  (1 << 2) //Clear FIFO transmitter symbols
#define AUX_MU_IIR_FIFO_ENABLE    (3 << 6) //FIFO RX and TX are both already enabled for BCM2835 default use this to re-enable FIFO in case it's off 
#define AUX_MU_IIR_FIFO_DISABLE  ~(3 << 6)

/* Mini UARt IER bits */
#define AUX_MU_IER_TX_INTERRUPT_ENABLE (1 << 1)
#define AUX_MU_IER_RX_INTERRUPT_ENABLE (1 << 0)


/* BAUD RATE CALCULATOR */

#define AUX_UART1_DEFAULT_CLK 250000000 
//#define AUX_UART1_CUSTOM_CLK // Define this macro for different sys clk
#define AUX_UART1_DEFAULT_BAUD_RATE 115200

#ifdef AUX_UART1_CUSTOM_CLK

	#define AUX_UART1_BAUD_DIVISOR(baud_rate) (AUX_UART1_CUSTOM_CLK / (8 * (baud_rate)) - 1)

#else

	#define AUX_UART1_BAUD_DIVISOR(baud_rate) (AUX_UART1_DEFAULT_CLK / (8 * (baud_rate)) - 1)

#endif

#endif

/* Struct Mini uart settings and data settings */

typedef struct mini_uart_data_settings {
        volatile unsigned int size;
	volatile char *data;
      	volatile unsigned int data_size; 	
}mini_data_set;


typedef struct mini_uart_settings{
	unsigned int baud_rate;
        unsigned int tx_enable;
        unsigned int rx_enable;
        unsigned int fifo_enable; 
	struct mini_uart_data_settings *data_settings;
}set_mini_uart;


void uart1_puts(int char_count, volatile char *str );
void uart1_putc(volatile char character);
volatile char uart1_getc();
set_mini_uart * uart1_init(set_mini_uart * mini_set);
void mini_uart_driver_setup();
