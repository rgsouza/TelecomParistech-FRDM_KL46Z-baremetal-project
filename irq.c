#include"irq.h"

#define VTOR (*(volatile uint32_t*) 0xE000ED08)
#define NVIC_ISER (*(volatile uint32_t*) 0xE000E100 )
#define NVIC_ICER (*(volatile uint32_t*) 0xE000E180 )


#define MAKE_DEFAULT_HANDLER(nameHandler) void __attribute__((weak)) nameHandler( void ) {disable_irq();while(1);}

// Déclaration et instanciation des fonctions d'exception interne.
MAKE_DEFAULT_HANDLER(NMI_Handler);
MAKE_DEFAULT_HANDLER(HardFault_Handler);
MAKE_DEFAULT_HANDLER(SVC_Handler);
MAKE_DEFAULT_HANDLER(PendSV_Handler);
MAKE_DEFAULT_HANDLER(SysTick_Handler);

// Déclaration et instanciation des fonctions d'interruption externe.
MAKE_DEFAULT_HANDLER(DMA0_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA3_IRQHandler);
MAKE_DEFAULT_HANDLER(FTFA_IRQHandler);
MAKE_DEFAULT_HANDLER(PMC_IRQHandler);
MAKE_DEFAULT_HANDLER(LLWU_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C0_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C1_IRQHandler);
MAKE_DEFAULT_HANDLER(SPI0_IRQHandler);
MAKE_DEFAULT_HANDLER(SPI1_IRQHandler);
MAKE_DEFAULT_HANDLER(UART0_IRQHandler);
MAKE_DEFAULT_HANDLER(UART1_IRQHandler);
MAKE_DEFAULT_HANDLER(UART2_IRQHandler);
MAKE_DEFAULT_HANDLER(ADC0_IRQHandler);
MAKE_DEFAULT_HANDLER(CMP0_IRQHandler);
MAKE_DEFAULT_HANDLER(TPM0_IRQHandler);
MAKE_DEFAULT_HANDLER(TPM1_IRQHandler);
MAKE_DEFAULT_HANDLER(TPM2_IRQHandler);
MAKE_DEFAULT_HANDLER(RTC0_IRQHandler);
MAKE_DEFAULT_HANDLER(RTC1_IRQHandler);
MAKE_DEFAULT_HANDLER(PIT_IRQHandler);
MAKE_DEFAULT_HANDLER(I2S0_IRQHandler);
MAKE_DEFAULT_HANDLER(USB_OTG_IRQHandler);
MAKE_DEFAULT_HANDLER(DAC0_IRQHandler);
MAKE_DEFAULT_HANDLER(TSI0_IRQHandler);
MAKE_DEFAULT_HANDLER(MCG_IRQHandler);
MAKE_DEFAULT_HANDLER(LPTMR0_IRQHandler);
MAKE_DEFAULT_HANDLER(SLCD_IRQHandler);
MAKE_DEFAULT_HANDLER(PORTA_IRQHandler);
MAKE_DEFAULT_HANDLER(PORTCD_IRQHandler);

void _start();
extern char _stack;


// Vector_table est placé dans la section .interrupts.
void *vector_table[] __attribute__((section(".interrupts"))) = {

	// Sommet du stack pointer
	&_stack,            

	// Reset handler
	_start, 

	// ARM exception internes.
	NMI_Handler,        
	HardFault_Handler,  
	0,                  
	0,                  
	0,                  
	0,                  
	0,                  
	0,                  
	0,                  
	SVC_Handler,        
	0,                  
	0,                  
	PendSV_Handler,     
	SysTick_Handler,    

	// KL46 interruptions externes.
	DMA0_IRQHandler,
	DMA1_IRQHandler,
	DMA2_IRQHandler,
	DMA3_IRQHandler,
	0,
	FTFA_IRQHandler,
	PMC_IRQHandler,
	LLWU_IRQHandler,
	I2C0_IRQHandler,
	I2C1_IRQHandler,
	SPI0_IRQHandler,
	SPI1_IRQHandler,
	UART0_IRQHandler,
	UART1_IRQHandler,
	UART2_IRQHandler,
	ADC0_IRQHandler,
	CMP0_IRQHandler,
	TPM0_IRQHandler,
	TPM1_IRQHandler,
	TPM2_IRQHandler,
	RTC0_IRQHandler,
	RTC1_IRQHandler,
	PIT_IRQHandler,
	I2S0_IRQHandler,
	USB_OTG_IRQHandler,
	DAC0_IRQHandler,
	TSI0_IRQHandler,
	MCG_IRQHandler,
	LPTMR0_IRQHandler,
	SLCD_IRQHandler,
	PORTA_IRQHandler,
	PORTCD_IRQHandler
};

void irq_init( void )
{
	VTOR =(uint32_t) &vector_table;
}

void irq_enable( int irq_number )
{
	NVIC_ISER = (1 << irq_number);
}

void irq_disable( int irq_number )
{
	NVIC_ICER = (1 << irq_number);

}
