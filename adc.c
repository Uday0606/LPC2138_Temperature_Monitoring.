
#include <LPC213x.h>
#include "defines.h"
#include "adc.h"

#define ADC_CLKDIV 15   // CPU 60MHz -> ADC = 4 MHz (valid)
#define LM35_ADC_CH 5        // AD0.5 on P0.26

void ADC_Init(void)
{
    // Configure P0.26 as AD0.5
    CFGPIN(PINSEL1, 20, FUN1);   // PINSEL1[21:20] = 01 for AD0.5

    AD0CR = 0;                    // Clear AD0CR

    AD0CR |= (1 << 21);           // PDN = 1 (ADC power on)
    AD0CR |= (ADC_CLKDIV << 8);   // Set CLKDIV
    AD0CR |= (1 << LM35_ADC_CH);  // Select channel AD0.5
}

unsigned int ADC_Read(void)
{
    unsigned int value;

    // Start conversion
    AD0CR &= ~(7 << 24);       // Clear START bits
    AD0CR |=  (1 << 24);       // START = 001 (software start)

    // Wait until conversion done
    while (!(AD0GDR & (1UL << 31)));

    // Read 10-bit result
    value = (AD0GDR >> 6) & 0x3FF;

    return value;
}

