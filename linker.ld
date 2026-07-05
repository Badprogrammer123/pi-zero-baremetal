ENTRY(_start)

MEMORY 
{
	RAM(rwx) : ORIGIN = 0x8000, LENGTH =437868K
      
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

	.vector_base_table : {
		. = LENGTH(RAM) - 8000; 
		. = ALIGN(32);
		__vector_base_table_start = . ;
		
		__vector_base_table_end = . + 2000000;  
	}

}



