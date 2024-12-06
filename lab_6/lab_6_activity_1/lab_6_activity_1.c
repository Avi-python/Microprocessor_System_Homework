#include <reg51.h>

// 411085025
// group 4

sbit OUTPUT = P0^1;

void T0Delay();

void main(void)
{
		for(;;)
		{
			OUTPUT = 0;
			T0Delay();
			OUTPUT = 1;
			T0Delay();
		}
}

void T0Delay()
{
	TMOD = 0x01;
	TL0 = 0x34;
	TH0 = 0xFE;
	TR0 = 1;
	while(TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}