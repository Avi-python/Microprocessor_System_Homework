#include <reg51.h>

// 411085025
// group 4

#define XTALHZ 24000000
#define OFFSET 18

#define SEC_TO_LOOP 15

#define DO  262
#define RE  294
#define MI  330
#define FA  349  
#define SO  392    
#define LA  440
#define TI  494

#define LED_OUTPUT P1
sbit BUZ_OUTPUT = P0^1;

static unsigned int toneLoops[21];
volatile unsigned int wave_duration;
volatile unsigned int play_duration_loop;
volatile unsigned char tone;

void setup();
void displayLED(unsigned char);
void start();
void playOffISR();
void waveISR();
void buildTable();

void main(void)
{
	setup();
	buildTable();
	start();
	for(;;)
	{
		
	}
}

void setup()
{
	// setup timer
	TMOD = 0x11;
	IE = 0x8A; // enable timer 1 and timer 0 interr.
	tone = 0;
}

void start()
{
	wave_duration = toneLoops[tone];
	play_duration_loop = 0;
	TL1 = 0x00;
	TH1 = 0x00;
	TL0 = wave_duration;
	TH0 = wave_duration >> 8;
	displayLED(tone);
	BUZ_OUTPUT = 0;
	TR1 = 1;
	TR0 = 1;
}

void playOffISR() interrupt 3
{
	TR1 = 0; // stop timer 1
	play_duration_loop++;
	if(play_duration_loop == SEC_TO_LOOP * 1)
	{
		play_duration_loop = 0;
		TR0 = 0; // stop timer 0
		TF1 = 0;
		// next round
		tone = (tone + 1) % 21;
		wave_duration = toneLoops[tone];
		displayLED(tone);
		TL0 = wave_duration;
		TH0 = wave_duration >> 8;
		TR1 = 1;
		TR0 = 1;
	}
	TR1 = 1;
}

void waveISR() interrupt 1
{
	TR0 = 0;
	BUZ_OUTPUT = ~BUZ_OUTPUT;
	TL0 = wave_duration;
	TH0 = wave_duration >> 8;
	TR0 = 1;
}

void displayLED(unsigned char target)
{
	LED_OUTPUT = ~target;
}

void buildTable()
{
	unsigned loop;
	toneLoops[0] = DO / 2;
	toneLoops[1] = RE / 2;
	toneLoops[2] = MI / 2;
	toneLoops[3] = FA / 2;
	toneLoops[4] = SO / 2;
	toneLoops[5] = LA / 2;
	toneLoops[6] = TI / 2;
	toneLoops[7] = DO; // mid c
	toneLoops[8] = RE;
	toneLoops[9] = MI;
	toneLoops[10] = FA;
	toneLoops[11] = SO;
	toneLoops[12] = LA;
	toneLoops[13] = TI;
	toneLoops[14] = DO * 2;
	toneLoops[15] = RE * 2;
	toneLoops[16] = MI * 2;
	toneLoops[17] = FA * 2;
	toneLoops[18] = SO * 2;
	toneLoops[19] = LA * 2;
	toneLoops[20] = TI * 2;
	for(loop = 0; loop < 21; loop++)
	{
		toneLoops[loop] = 65536 - XTALHZ / (24 * toneLoops[loop]) + OFFSET;
	}
}
