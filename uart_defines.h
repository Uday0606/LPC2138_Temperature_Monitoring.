                       
     //uart_defines.h
#define TXD0_0_0 FUN2
#define RXD0_0_1 FUN2
//divisor calculaation
#define FOSC 12000000
#define CCLK FOSC*5
#define PCLK CCLK/4
#define BAUD 9600
#define DIVISOR (PCLK/(16*BAUD))
//UOLCR defines
#define WORD_LEN_8 3
#define DLAB_BIT 7
//UOLSR defines
#define DR_BIT 0
#define THRE_BIT 5
#define TEMT_BIT 6
