/* Auteur Rayanne Goncalves */

.thumb
.thumb_func
.global _start
.extern copy_rom_ram
.extern init_bss
.extern main


_start:
	ldr r0,=_stack
	mov sp,r0
	movs r0, #0

	bl copy_rom_ram
	bl init_bss	
	bl main
	
loop:	b loop	
