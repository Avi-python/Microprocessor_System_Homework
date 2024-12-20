#include <reg51.h>

// 411085025
// group 4

#define XTALHZ 11059200
#define OFFSET 18

#define DO  262
#define RE  294
#define MI  330
#define FA  349  
#define SO  392    
#define LA  440
#define TI  494    

#define SEG_OUTPUT P1
sbit BUZ_OUTPUT = P0^1;

static unsigned int toneLoops[21];

void playToneAndSegment(unsigned char);
void displaySegment(unsigned char);
void playTone(unsigned char);
void T0Delay(unsigned int);
void buildTable();

void main(void)
{
	TMOD = 0x11;
	buildTable();
	for(;;)
	{
		unsigned char loop;
		unsigned char index;
		for(index = 0; index < 14; index++)
		{
			for(loop = 0; loop < 7; loop++)
			{
				playToneAndSegment(index);
			}
		}
	}
}

void playToneAndSegment(unsigned char target)
{
	displaySegment(target);
	playTone(target);
}

void playTone(unsigned char tone)
{
	displaySegment(tone);
	TL1 = 0x00;
	TH1 = 0x00;
	TR1 = 1;
	while(TF1 == 0)
	{
		BUZ_OUTPUT = 0;
		T0Delay(toneLoops[tone]);
		BUZ_OUTPUT = 1;
		T0Delay(toneLoops[tone]);
	}
	TF1 = 0;
	TR1 = 0;
}

void T0Delay(unsigned int loops)
{
	TL0 = loops;
	TH0 = loops >> 8;
	TR0 = 1;
	while(TF0 == 0);
	TF0 = 0;
	TR0 = 0;
}

void displaySegment(unsigned char target)
{
	switch(target)
	{
		case 0:
			{
				SEG_OUTPUT = 0xC0;
				break;
			}
		case 1:
			{
				SEG_OUTPUT = 0xF9;
				break;
			}
		case 2:
			{
				SEG_OUTPUT = 0xA4;
				break;
			}
		case 3:
			{
				SEG_OUTPUT = 0xB0;
				break;
			}
		case 4:
			{
				SEG_OUTPUT = 0x99;
				break;
			}
		case 5:
			{
				SEG_OUTPUT = 0x92;
				break;
			}
		case 6:
			{
				SEG_OUTPUT = 0x82;
				break;
			}
		case 7:
			{
				SEG_OUTPUT = 0xD8;
				break;
			}
		case 8:
			{
				SEG_OUTPUT = 0x80;
				break;
			}
		case 9:
			{
				SEG_OUTPUT = 0x90;
				break;
			}
		case 10:
			{
				SEG_OUTPUT = 0x88;
				break;
			}
		case 11:
			{
				SEG_OUTPUT = 0x83;
				break;
			}
		case 12:
			{
				SEG_OUTPUT = 0xC6;
				break;
			}
		case 13:
			{
				SEG_OUTPUT = 0xA1;
				break;
			}
	}
}

void buildTable()
{
	unsigned loop;
	toneLoops[0] = DO;
	toneLoops[1] = RE;
	toneLoops[2] = MI;
	toneLoops[3] = FA;
	toneLoops[4] = SO;
	toneLoops[5] = LA;
	toneLoops[6] = TI;
	toneLoops[7] = DO * 2;
	toneLoops[8] = RE * 2;
	toneLoops[9] = MI * 2;
	toneLoops[10] = FA * 2;
	toneLoops[11] = SO * 2;
	toneLoops[12] = LA * 2;
	toneLoops[13] = TI * 2;
	for(loop = 0; loop < 14; loop++)
	{
		toneLoops[loop] = 65536 - XTALHZ / (24 * toneLoops[loop]) + OFFSET;
	}
}

