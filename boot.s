.extern __stack_top
 
.extern kernel_main

.global _start


_start:
	
	ldr sp, =__stack_top
	b kernel_main
