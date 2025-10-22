#ifndef MCAL_UART_UART_CONF_H_
#define MCAL_UART_UART_CONF_H_

/*select baud rate of data 
 ** Options
   *2400
   *4800
   *9600
   *14400
   *19200
   *28800
   *38400
   *57600
   *76800
   *115200
   *230400
   *250000
   *500000
   *1000000
 */
#define BAUD_RATE  9600

/*select number of data bits to be sent or received 
 **Options
    *5
	*6
	*7
	*8
 */
#define NUMBER_OF_DATA_BITS  8
#endif /* MCAL_UART_UART_CONF_H_ */
