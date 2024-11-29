#include <reg51.h>

// 411085025
// group 4

#define INPUT P2
#define OUTPUT P1

void displayNToZero(unsigned char);
void displayN(unsigned char);
void displayNone();
void MSDelay(unsigned int);

void main(void)
{
	INPUT = 0xFF;
	for(;;)
	{
			unsigned char loop = 8;
			unsigned char enable_bit = 0x80;
			while(loop > 0)
			{
					if((~INPUT) & enable_bit)
					{
						displayNToZero(loop);
						break;
					}
					enable_bit = enable_bit >> 1;
					loop--;
			}
	}
}

void displayNToZero(unsigned char target)
{
	unsigned char count = 0;
	while(count <= target)
	{
		displayN(count);
		MSDelay(1000);
		count++;
	}
	displayNone();
}

void displayN(char target)
{
	switch(target)
	{
		case 0:
			{
				OUTPUT = 0xC0;
				break;
			}
		case 1:
			{
				OUTPUT = 0xF9;
				break;
			}
		case 2:
			{
				OUTPUT = 0xA4;
				break;
			}
		case 3:
			{
				OUTPUT = 0xB0;
				break;
			}
		case 4:
			{
				OUTPUT = 0x99;
				break;
			}
		case 5:
			{
				OUTPUT = 0x92;
				break;
			}
		case 6:
			{
				OUTPUT = 0x82;
				break;
			}
		case 7:
			{
				OUTPUT = 0xD8;
				break;
			}
		case 8:
			{
				OUTPUT = 0x80;
				break;
			}
		case 9:
			{
				OUTPUT = 0x90;
				break;
			}
	}
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