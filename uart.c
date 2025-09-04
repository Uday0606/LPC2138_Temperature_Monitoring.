
#include <LPC213x.h>
#include "uart.h"
#include "uart_defines.h"
#include "defines.h"

void __irq UART0_IRQHandler(void);   // forward declaration

volatile unsigned char received_data = 0; // updated by ISR

void InitUART()
{
	CFGPIN(PINSEL0,0,TXD0_0_0);
	CFGPIN(PINSEL0,1,RXD0_0_1);
	U0LCR=(1<<DLAB_BIT)|WORD_LEN_8;
	U0DLL=DIVISOR;
	U0DLM=DIVISOR>>8;
	CLRBIT(U0LCR,DLAB_BIT);
	U0IER=0X01;
}

void Enable_Global_Interrupts()
{
    __asm {
        MRS R0, CPSR
        BIC R0, R0, #0x80  // Clear I-bit (Enable IRQ)
        MSR CPSR_c, R0
    }
}

void Enable_UART_Interrupt()
{
    VICIntEnable |= (1 << 6);      // Enable UART0 interrupt (ch 6)
    VICVectCntl0 = (1<<5) | 6;     // Slot 0, enable, UART0 source
    VICVectAddr0 = (unsigned long)UART0_IRQHandler; // ISR address
}

// ---------------- UART ISR ----------------
void __irq UART0_IRQHandler(void)
{
    unsigned char iir_status = U0IIR & 0x0E; // bits [3:1]

    if (iir_status == 0x04) // Data received
    {
        received_data = U0RBR; // Store data
    }

    VICVectAddr = 0; // Acknowledge interrupt
}

void charUART_tx(unsigned char sdat)
{
	U0THR=sdat;
	while(READBIT(U0LSR,TEMT_BIT)==0);
}
void strUART_tx(char *p)
{
	while(*p)
	{
		charUART_tx(*p++);
	}
}


char UART0_RxChar(void)
{
    while (!(U0LSR & (1 << 0)));  // wait until RDR (data ready)
    return U0RBR;
}



