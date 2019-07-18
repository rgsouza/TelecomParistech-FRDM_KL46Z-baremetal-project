#ifndef BUTTONS_H
#define BUTTONS_H
 
// Active l'horloge du port C, configure la broche PORTC3 en entrée et GPIO.
// Configure cette broche avec pull-up et interruption sur front descendant.
// Active l'nterruption du PORTC.
void button_init( void );
	
#endif 
