/* Auteur Rayanne Goncalves */

extern char _bstart, _bend, _erodata, _interrupt, _einterrupt, _lmaInterrupt;
extern char _text, _etext, _data,_edata, _init;


void copy_rom_ram()
{
	char *src = &_erodata;
	char *dst = &_data;
	
	// recopie les donnees de la flash vers la ram.
	while ( dst < &_edata )
		*dst++ = *src++;

	src = &_init;
	dst = &_text;
	while( dst < &_etext )
		*dst++ = *src++;

	// recopie la section interrupt de la flash vers la ram.
	dst = &_interrupt;
	src = &_lmaInterrupt;
	while( dst < &_einterrupt )
		*dst++ = *src++;

}

void init_bss()
{
	// Met le bss à zero.
	char *pbss;
	for( pbss = &_bstart; pbss < &_bend; pbss++ )
		*pbss = 0;
}

