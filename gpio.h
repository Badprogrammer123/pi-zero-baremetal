#ifndef GPIO_PINS

#define GPIO_PINS

/* GPIO PINS  */
#define GPIO14_TX_MODE           (1 << 13) 
#define GPIO15_RX_MODE           (1 << 16)
#define GPIO14_CLEAR             (7 << 12) 
#define GPIO15_CLEAR             (7 << 15)


/* GPIO BASE ADDRESS */
#define GPIO_BASE       (*(volatile unsigned int *) 0x3F200000) 

/* GPIO FUNCTION SELECT */
#define GPFSEL1          (*(volatile unsigned int *) 0x3F200004)


#endif 



