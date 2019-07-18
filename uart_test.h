#ifndef UART_TEST_H
#define UART_TEST_H

#include"uart.h"

uint32_t uart_sum_bytes( uint8_t vbytes, int size )
{
	uint32_t sum  = 0;
		
	for( int i = 0; i < size; i++)
	{	vbytes[i] = uart_getchar();
		sum += vbytes[i];
	}
	return sum;

}

#endif 
