.extern __stack_top
 
.extern kernel_main

.global _start


_start:
	mov r0, #666
	ldr sp, =__stack_top
	b kernel_main
