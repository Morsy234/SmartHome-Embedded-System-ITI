#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_

void MUART_voidInit (void) ;

void MUART_voidSendData(u8 A_u8Data) ;

u8 MUART_u8ReceiveData(void) ;

void MUART_voidSendString(u8* A_pu8Str) ;

#endif /* MCAL_UART_UART_INT_H_ */
