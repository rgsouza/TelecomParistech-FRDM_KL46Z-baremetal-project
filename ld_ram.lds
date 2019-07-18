/* Auteur Rayanne Goncalves*/

ENTRY(_start)

MEMORY{

	flash_interrupt(rx) : ORIGIN = 0x0, LENGTH = 192 
	flash_config (rx): ORIGIN = 0x400, LENGTH = 16
	flash_code(rx) : ORIGIN = 0x1000, LENGTH = 252K
	raml(!rx) : ORIGIN = 0x1fffe000, LENGTH = 8K
	ramh(!rx) : ORIGIN = 0x20000000, LENGTH = 24K
	
}

_stack = ORIGIN(raml) + LENGTH(raml);

SECTIONS {

	.flash_config : {

		*(.flash_config)

	}>flash_config	


	/* Ne mettez aucune autre section à être recopier vers ram au-déssus de celle-là.*/
	.interrupts : {

		_lmaInterrupt = ORIGIN( flash_interrupt );
		_interrupt = .; 
		*(.interrupts)
		_einterrupt = .;

	} > ramh AT > flash_interrupt

	.init : {
		init.o (.text )
		crt0.o (.text )
		_init = .;
	} > flash_code

	.text : {
		_text = .;
		*(.text)
		_etext = .;
	} > ramh AT > flash_code


	.rodata : {
		*(.rodata)
		_erodata = .;
	}>flash_code

	.data : {
		_data = .;
		*(.data)
		_edata = .;

	} > ramh AT > flash_code


	.bss : {
		_bstart = . ;	
		*(.bss) *(COMMON)
		_bend = . ;
	}>ramh
	
}

