#include <reg51.h>

// 411085025
// group 4

#define INPUT P2
#define OUTPUT P1

extern unsigned char _listen(void);
void displayAsciiN(unsigned char);
void displayNone();
unsigned char numToAscii(unsigned char);
void MSDelay(unsigned int);

void main(void)
{
	INPUT = 0xFF;
	displayNone();
	for(;;)
	{
		unsigned char x;
		x = _listen();
		if(x == 0)
		{
			displayNone();
		}
		else
		{
			displayAsciiN(x);
		}
	}
}

void displayAsciiN(unsigned char target)
{
	OUTPUT = ~numToAscii(target);
	MSDelay(1000);
	displayNone();
}

unsigned char numToAscii(unsigned char target)
{
	return 0x30 | target;
}

void displayNone()
{
	OUTPUT = 0xFF;
}

void MSDelay(unsigned int itime)
{
	unsigned int i, j;
	for(i=0;i<itime;i++)
	for(j=0;j<113;j++);
}