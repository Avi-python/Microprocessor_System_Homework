#include <reg51.h>
#include <INTRINS.h>

// 411085025
// group 4

#define MAX 65536

#define MC 12
#define XTALHZ 24000000

#define OFFSET 18

#define C3	MAX - XTALHZ / (2 * MC * 131) + OFFSET
#define D3	MAX - XTALHZ / (2 * MC * 147) + OFFSET
#define E3 	MAX - XTALHZ / (2 * MC * 165) + OFFSET
#define F3 	MAX - XTALHZ / (2 * MC * 175) + OFFSET
#define G3 	MAX - XTALHZ / (2 * MC * 196) + OFFSET
#define A3	MAX - XTALHZ / (2 * MC * 220) + OFFSET
#define B3 	MAX - XTALHZ / (2 * MC * 247) + OFFSET
#define C4	MAX - XTALHZ / (2 * MC * 262) + OFFSET
#define D4	MAX - XTALHZ / (2 * MC * 294) + OFFSET
#define E4 	MAX - XTALHZ / (2 * MC * 330) + OFFSET
#define F4 	MAX - XTALHZ / (2 * MC * 349) + OFFSET
#define G4 	MAX - XTALHZ / (2 * MC * 392) + OFFSET
#define A4	MAX - XTALHZ / (2 * MC * 440) + OFFSET
#define B4 	MAX - XTALHZ / (2 * MC * 494) + OFFSET
#define C5	MAX - XTALHZ / (2 * MC * 523) + OFFSET
#define D5	MAX - XTALHZ / (2 * MC * 587) + OFFSET
#define E5 	MAX - XTALHZ / (2 * MC * 659) + OFFSET
#define F5 	MAX - XTALHZ / (2 * MC * 698) + OFFSET
#define G5 	MAX - XTALHZ / (2 * MC * 784) + OFFSET
#define A5	MAX - XTALHZ / (2 * MC * 880) + OFFSET
#define B5 	MAX - XTALHZ / (2 * MC * 988) + OFFSET
#define OO 	0 // rest
#define	NN	1 // link

#define LED_OUTPUT P1
sbit BUZ_OUTPUT = P0^1;

// define the basic duration of a note
#define PARAG	25
#define TEMPO 10
#define TEMPO_OFFSET_L 0xC0
#define TEMPO_OFFSET_H 0x0B

code unsigned int song[PARAG][8] = {
	{OO, OO, OO, OO, OO, OO, C4, D4},
	{E4, NN, D4, E4, F4, NN, E4, F4},
	{G4, NN, C4, NN, OO, OO, C4, G3},
	{A3, NN, A3, C4, B3, NN, C4, D4},
	{E4, NN, NN, NN, OO, OO, C4, D4},
	{E4, NN, D4, E4, F4, NN, E4, F4},
	{G4, C5, B4, C5, A4, NN, OO, A4},
	{G4, F4, E4, F4, E4, NN, D4, NN},
	{C4, NN, NN, NN, OO, OO, OO, C4},
	{A3, C4, C4, A4, G4, NN, OO, C4},
	{A3, C4, C4, F4, E4, NN, OO, C4},
	{A3, C4, C4, A4, G4, NN, C5, NN},
	{A4, G4, F4, A4, G4, NN, NN, G4},
	{C5, NN, D5, C5, B4, NN, C5, NN},
	{A4, A4, C5, A4, G4, NN, OO, C4},
	{F4, G4, A4, B4, C5, NN, G4, NN},
	{F4, E4, D4, C4, D4, NN, OO, G4},
	{C5, NN, D5, C5, B4, NN, C5, NN},
	{A4, A4, C5, D5, C5, NN, NN, NN},
	{A4, B4, C5, NN, E4, F4, G4, NN},
	{F4, G4, F4, E4, D4, NN, B3, NN},
	{C4, NN, NN, NN, NN, NN, OO, OO},
	{OO, OO, OO, OO, OO, OO, OO, OO},
	{OO, OO, OO, OO, OO, OO, OO, OO},
	{OO, OO, OO, OO, OO, OO, OO, OO}
};

volatile unsigned int wave_duration;
volatile unsigned int pre_wave;
volatile unsigned int play_duration_loop;
volatile unsigned char paragraph;
volatile unsigned char note_index;

void setup();
void displayLED(unsigned char);
void start();
void songManagerISR();
void waveISR();
void stopISR();
void startISR();

void main(void)
{
	setup();
	while(1);
}

void setup()
{
	// setup timer
	TMOD = 0x11;
	IE = 0x8F; // enable timer 1 and timer 0 interr.
	IT0 = 1; // set external interrupt to edge-triggered mode
	IT1 = 1;
}

void start()
{
	paragraph = 0;
	note_index = 0;
	wave_duration = song[paragraph][note_index];
	play_duration_loop = 0;
	TL1 = TEMPO_OFFSET_L;
	TH1 = TEMPO_OFFSET_H;
	TL0 = wave_duration;
	TH0 = wave_duration >> 8;
	displayLED(paragraph + 5);
	BUZ_OUTPUT = 0;
	TR1 = 1;
	TR0 = 1;
}

void songManagerISR() interrupt 3
{
	TR1 = 0; // stop timer 1
	TL1 = TEMPO_OFFSET_L;
	TH1 = TEMPO_OFFSET_H;
	play_duration_loop++;
	if(play_duration_loop == TEMPO)
	{
		// next round
		play_duration_loop = 0;
		TF1 = 0;
		note_index++;
		if(note_index == 8)
		{
			paragraph = (paragraph + 1) % PARAG;
			note_index = 0;
		}
		wave_duration = song[paragraph][note_index];
		if(wave_duration != NN)
		{
			pre_wave = wave_duration;
			TR0 = 0; // stop timer 0
			TL0 = wave_duration;
			TH0 = wave_duration >> 8;
			TR0 = 1;
		}
		else
		{
			wave_duration = pre_wave;
		}
	}
	TR1 = 1; // restart timer 1
	displayLED(paragraph + 5);
}

void waveISR() interrupt 1
{
	TR0 = 0;
	BUZ_OUTPUT = wave_duration == 0 ? 0 : ~BUZ_OUTPUT;
	TL0 = wave_duration;
	TH0 = wave_duration >> 8;
	TR0 = 1;
}

void stopISR() interrupt 0
{
	TR0 = 0;
	TR1 = 0;
}

void startISR() interrupt 2
{
	if(TR1 == 0) // avoid restart while playing music
	{
		start();
	}
}

void displayLED(unsigned char target)
{
	LED_OUTPUT = ~target;
}
