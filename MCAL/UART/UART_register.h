#ifndef MCAL_UART_UART_REGISTER_H_
#define MCAL_UART_UART_REGISTER_H_

/*USART data register*/
#define UDR	    *((volatile u8 *)(0x2C))

/*USART control and status register A*/
#define UCSRA   *((volatile u8 *)(0x2B))

/*USART control and status register B*/
#define UCSRB   *((volatile u8 *)(0x2A))

/*USART control and status register C*/
#define UCSRC   *((volatile u8 *)(0x40))

/*USART baud rate register low*/
#define UBRRL   *((volatile u8 *)(0x29))

/*USART baud rate register high*/
#define UBRRH   *((volatile u8 *)(0x40))


#endif /* MCAL_UART_UART_REGISTER_H_ */
