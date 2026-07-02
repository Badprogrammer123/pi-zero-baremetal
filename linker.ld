ENTRY(_start)

MEMORY 
{
	RAM(wx) : ORIGIN = 0x8000, LENGTH =64M
      
}

SECTIONS
{
	. = 0x8000; 
	.text : {
		boot.o 
		*(.text)

	}	

	.data : {
		*(.data)
	} 
	__bss_start = . ;

	.bss : {
		*(.bss)
		*(COMMON)
	}
	 __bss_end = . ;
	
	.rodata : { 
		*(.rodata) 
	}
	

	__stack_top = ORIGIN(RAM) + LENGTH(RAM); 

}



