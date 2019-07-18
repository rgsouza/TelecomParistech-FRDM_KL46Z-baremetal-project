#include"mcg_registers.h"
#include"sim_registers.h"

// Passage du mode FEI au mode FBE.
static void FEI_to_FBE();

// Passage du mode FBE au mode PBE.
static void FBE_to_PBE();

// Passage du mode PBE au mode PEE.
static void PBE_to_PEE();

void clocks_init ()
{
	// Desactive COP whatch dog operation
	SIM_COPC = 0;

	FEI_to_FBE();
	FBE_to_PBE();
	PBE_to_PEE();
	
	// Configure Bus clock et flash clock à 24MHz ( 48MHz divide-by-2).
	// Configure Core clock, Platform clock et System Clock à 48MHz ( 48 MHz divide-by-1).
	SIM_CLKDIV1 = 0x10000;

}


// Passage du mode FEI au mode FBE.
static void FEI_to_FBE()
{
	// Selectionne l'option haute frequence.
        // Configure crystal oscillator pour high-gain operation.
        // Selectionne l'utilisation du crystal oscillator (EREFS0).
	MCG_C2 = 0x1C;

        // Selectionne horloge de reference externe
        // Configure pour 8MHz avec 256 de division. 
	MCG_C1 = 0x98;

        // Attend que le crystal oscillator soit initialisé.
        // Sort de la boucle indiquant l'initialisation du oscillator.
        for ( int i = 0; i < 20000; i++ )
        {       // Test OSCINIT0 
                if ( MCG_S & 0x2 ) break;
        }

        // Attend que horloge de reference externe soit utilisé. 
        for ( int i = 0; i < 2000; i++)
        {       // Teste IREFST
                if( !(MCG_S & 0x10) ) break;
        }

        // Sort de la boucle quand le mode courant est horloge de reference externe.
        for ( int i = 0; i < 2000; i++ )
        {       // Teste CLKST
                if( MCG_S & 0x8 ) break;
        }

}

// Passage du mode FBE au mode PBE.
static void FBE_to_PBE ()
{
	// Active External clock monitor.
	// Active PLL et selectionne facteur de multiplication equal à 24
	MCG_C6 = 0x40;

	// PLL divide par 4. 
	MCG_C5 = 0x3;
		
        
        // Sort de la boucle si PLLST est 1.
        for ( int i = 0; i < 2000; i++ )
        {       // Teste PLLST.
                if( MCG_S & 0x20 ) break;
        }

        // Sort de la boucle si LOCK0 est 1.
        for ( int i = 0; i < 4000; i++ )
        {       // Teste LOCK0
                if( MCG_S & 0x40 ) break;
        }

}

// Passage du mode PBE au mode PEE.
static void PBE_to_PEE()
{
	// Selectionne PLL . 
        MCG_C1 &= ~0xC0;

        // Attend que PLL output soit selectionné.
        for( int i = 0; i < 2000; i++ )
        {       // Teste si CLKST indique output de PLL. 
                if ( (MCG_S & 0x4) && (MCG_S & 0x8)  ) break;
        }
}
