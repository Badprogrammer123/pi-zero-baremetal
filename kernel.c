#include <stdint.h>

#define PERIPHERAL_BASE 0x3F000000 
#define GPIO_BASE 0x3F200000 

#define GPFSEL2 (GPIO_BASE + 0x08)
#define GPCLR0 (GPIO_BASE + 0x28)
#define GPSET0 (GPIO_BASE + 0x1c)

#define UART1_BASE 0x3F215000
#define GPFSEL1 0x3F200004

void kernel_main(){

	//GPIO pins set to ALT5
        volatile unsigned int *uart_regs = (volatile unsigned int *) UART1_BASE;
    	volatile unsigned int *set_pin_mode = (volatile unsigned int *) GPFSEL1;
    	volatile unsigned int *set_test =  (volatile unsigned int *) GPSET0;
	*set_pin_mode &= ~(63 << 12);
        *set_pin_mode |= (1 << 13);
	*set_pin_mode |= (1 << 16);


        volatile uint32_t baudrate = 250000000 / (8 * (115200 + 1));


        //mini uart needs to be set to 1 to be able to write to its registers 
        *(uart_regs + (0x4/4)) |= 1;

        //disable transmit and recv
        *(uart_regs + (0x60/4)) &= ~3;


        //clear DLAB access 
        *(uart_regs + (0x4C/4)) &= ~(1 << 7);



        //enable FIFO interrupt register
        *(uart_regs +  (0x44/4)) |= ~3;

        //uart baud rate
        *(uart_regs) |= baudrate;

        //set data register size to 8 bits
        *(uart_regs + (0x4C/4)) |= 1;


	//clear uart receive
	*(uart_regs + (0x48/4)) |= 2;

        //transmitter and Receiver set
        *(uart_regs + (0x60/4)) |= 3;

	*(uart_regs + (0x40/4)) &= 0; 
	while(1){
		if (((((*(uart_regs + (0x64/4))) >> 16) & 0x0F) + '0') == '8'){
			for(int i = 0; i < 8; i ++){
				char buffer = (char)(*(uart_regs + (0x40/4)));
				*(uart_regs + (0x40/4)) = buffer;
			}
		}	
		//How many bytes symbols in receive fifo 0-8 symbols only
		//*(uart_regs + (0x40/4)) =  ((((*(uart_regs + (0x64/4))) >> 16) & 0x0F) + '0');
	}
	
}
