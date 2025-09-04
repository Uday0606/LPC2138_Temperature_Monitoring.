#include <LPC213x.h>
#include <stdio.h>
#include "lcd.h"
#include "uart.h"
#include "delay.h"
#include "defines.h"
#include "uart_defines.h"
#include "lcd_defines.h"
#include "adc.h"

#define LED_GREEN   16 // P1.16
#define LED_YELLOW  17 // P1.17
#define LED_RED     18//  p1.18

#define TEMP_LOW    20
#define TEMP_MEDIUM 50


unsigned char mode = 1;  // default mode


// - Sensor -
unsigned int Read_Sensor(void)
{
    return ADC_Read();  // your ADC read function
}

// ---------------- LCD ----------------
void Display_LCD(unsigned int value)
{
   cmd_lcd(CLRLCD);
	cmd_lcd(0x80);
   str_lcd("Mode: LCD");
	delay_ms(1000);
	cmd_lcd(CLRLCD);
    cmd_lcd(0x80);
	str_lcd("TEMPERATURE:");
	delay_ms(1000);
	cmd_lcd(GOTO_LINE2_POS0);
	u32LCD(value);
	delay_ms(1000);
	
     
}

// ----- UART ----
void Display_UART(unsigned int value)
{
    char buffer[25];
    sprintf(buffer, "Temperature=%d\n", value);
    strUART_tx(buffer);
    
}

// ---LEDs ---
void Display_LED(unsigned int value)
{
    // OFF all LEDs
IOCLR1 = (1<<LED_GREEN) | (1<<LED_YELLOW) | (1<<LED_RED);


if (value < TEMP_LOW)// Turn ON specific LED
{
    IOSET1 = (1<<LED_GREEN);
}
else if (value < TEMP_MEDIUM)
{
    IOSET1=(1<<LED_YELLOW);
}
else
{
    IOSET1 = (1<<LED_RED);

}
}
unsigned int Convert_To_TempC(unsigned int adc_value)
{
    return (adc_value * 3300) / (1023 * 10);  // in °C
}


// -- MAIN ---
int main()
{
    // Configure LEDs as output
  IODIR1 |= (1<<LED_GREEN) | (1<<LED_YELLOW) | (1<<LED_RED);


    // Init peripherals
    init_lcd();
    InitUART();
    ADC_Init();
	
	
    Enable_UART_Interrupt();
    Enable_Global_Interrupts();

    strUART_tx("Select Mode (1=LCD, 2=UART, 3=LED)\r\n");

    

   while(1)
{
    unsigned int sensor = Read_Sensor();
    unsigned int tempC  = Convert_To_TempC(sensor);

    if (received_data != 0)
    {
        if (received_data == '1')
            Display_LCD(tempC);    // one-time update
        else if (received_data == '2')
            Display_UART(tempC);   // one-time print
        else if (received_data == '3')
            Display_LED(tempC);    // one-time LED update

        received_data = 0; // clear after handling
    }

    delay_ms(500);
}
}