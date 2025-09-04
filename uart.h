//uart.h
void InitUART(void);
void charUART_tx(unsigned char);
void strUART_tx(char *);
char UART_rx(void);
char UART0_RxChar(void);
 
void Enable_UART_Interrupt(void);
void Enable_Global_Interrupts(void);
extern volatile unsigned char received_data;
