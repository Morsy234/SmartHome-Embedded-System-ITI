#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"
#include "UART_register.h"
#include "UART_private.h"
#include "UART_conf.h"
#include "UART_int.h"
#define F_CPU 8000000UL /*frequancy of mc*/
#include <util/delay.h>
#include <stdlib.h>


void MUART_voidInit (void)
{
	u16 UBRR;
	/* choose baud rate */
#if BAUD_RATE == 2400 || BAUD_RATE == 4800 || BAUD_RATE == 9600
	UBRR = (F_CPU/(16*(u32)BAUD_RATE))-1;
	UBRRL = (u8)UBRR;
	UBRRH = (u8)(UBRR>>8);
#else
	#error "Select correct BAUD_RATE"
#endif

	/*Enable UART TRANSMITTER*/
	SET_BIT(UCSRB,TXEN);
	/*Enable UART RECEIVER*/
	SET_BIT(UCSRB,RXEN);

	/*SELECT UCSRC REG*/
	SET_BIT(UCSRC, URSEL);
	/* Choose  8-BITS number of bits of char size*/
	SET_BIT(UCSRC, UCSZ0);
	SET_BIT(UCSRC, UCSZ1);
	CLEAR_BIT(UCSRB, UCSZ2);

}

void MUART_voidSendData(u8 A_u8Data)
{
	/* WAIT FOR UDR BUFFER TO BE EMPTY*/
	while(GET_BIT(UCSRA,UDRE) == 0);
	UDR = A_u8Data;
}

u8 MUART_u8ReceiveData(void)
{
	/* WAIT FOR UDR BUFFER TO BE filled with unread data*/
	while(GET_BIT(UCSRA,RXC) == 0);
	return UDR;
}

void MUART_voidSendString(u8* A_pu8Str)
{
	while(*A_pu8Str != '\0')
	{
		MUART_voidSendData(*A_pu8Str);
		A_pu8Str++;
	}
	MUART_voidSendData('\n');

}
