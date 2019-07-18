// Auteur Rayanne Goncalves

#ifndef LED_H
#define LED_H


// Cette fonction habilite les ports D et E, connecte les broches aux GPIO, configure
// les broches en mode sortie et allume les leds rouge et verte.
void led_init();

// Toutes configurations pour utiliser la broche PCR 5 sont mises au état reset. 
void reset_config_led_g();

// Fonction qui allume la led rouge.
void led_r_on();

// Fonction qui eteint la led rouge.
void led_r_off();

// Fonction qui inverse l'etat de la led rouge.
void led_r_toggle();

// Fonction qui allume la led verte.
void led_g_on();

// Fonction qui eteint la rede verte.
void led_g_off();

// Fonction qui inverse le etat de la led verte.
void led_g_toggle();

#endif


