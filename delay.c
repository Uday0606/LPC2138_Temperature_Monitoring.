//delay.c
void delay_us(int delay)
{
	delay*=12;
		while(delay--);
}
void delay_ms(int delay)
{
	delay*=12000;
	while(delay--);
}
void delay_s(int delay)
{
	delay*=12000000;
	while(delay--);
}
