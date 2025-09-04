//lcd.c
//#include <LPC21xx.h>
#include <LPC213x.h>
#include "lcd.h"
#include "defines.h"
#include "lcd_defines.h"
#include "delay.h"


void init_lcd()
{
	WRITEBYTE(IODIR0,LCD_DATA,0XFF);
	SETBIT(IODIR0,RS);//16
	SETBIT(IODIR0,EN);//17
	SETBIT(IODIR0,RW);//18
	delay_ms(15);
	cmd_lcd(0x30);
	delay_ms(10);
	cmd_lcd(0x30);
	delay_us(100);
	cmd_lcd(0x30);
	cmd_lcd(MODE_8BIT_2LINE);//0X38
	cmd_lcd(SHIFT_CUR_RGT);//0X06
	cmd_lcd(DISP_ON_CUR_BLK);//0X0F
	cmd_lcd(CLRLCD);//0X01
}
void write_lcd(unsigned char dat)
{
	SCLRBIT(IOCLR0,RW);   //RW=0
	WRITEBYTE(IOPIN0,LCD_DATA,dat);
	SSETBIT(IOSET0,EN);   //EN=1
	delay_us(1);
	SCLRBIT(IOCLR0,EN);    //EN=0
	delay_ms(2);
}
void cmd_lcd(unsigned char cmd)
{
	SCLRBIT(IOCLR0,RS);  //RS=0//IOCLR0=(1<<LCD_RS);
	write_lcd(cmd);
}

void char_lcd(unsigned char ascii)
{
	SSETBIT(IOSET0,RS);
	write_lcd(ascii);
}
void str_lcd(const char *p)
{
	while(*p)
	{
		char_lcd(*p++);
	}
}
void u32LCD(int  n)
{
    unsigned char a[10];   // temp array to hold digits
    signed int  i=0;

    if(n==0)
    {
        char_lcd('0');   // if number is 0, just print '0'
    }
    else
    {
        while(n>0)
        {
            a[i++] = (n%10) + 48; // store last digit as ASCII
            n /= 10;              // remove last digit
        }

        for(--i; i>=0; i--)
        {
            char_lcd(a[i]);        // print digits in reverse order
        }
    }
}


