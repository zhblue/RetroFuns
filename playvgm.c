/* -------------------------------------------------------------------------- */
/*                                                                            */
/* FM synthesizer low-level interface demo program.                           */
/* Copyright (c) 1994 Creative Labs, Inc.                                     */
/*                                                                            */
/* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY      */
/* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE        */
/* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR      */
/* PURPOSE.                                                                   */
/*                                                                            */
/* You have a royalty-free right to use, modify, reproduce and                */
/* distribute the Sample Files (and/or any modified version) in               */
/* any way you find useful, provided that you agree that                      */
/* Creative has no warranty obligations or liability for any Sample Files.    */
/*                                                                            */
/*----------------------------------------------------------------------------*/
  
/*
 *  This Program is written using Borland C++ Ver 3.1.
 *  To Compile : BCC FMSAMPLE.C
 * ---------------------------------------------------------------------
 *
 * This program is not intended to explain all the aspects of FM sound
 * generation on Sound Blaster cards.  The chips are too complicated for
 * that.  This program is just to demonstrate how to generate a tone and
 * control the left and right channels.  For more information on the FM
 * synthesizer chip, contact Yamaha.
 *
 * Here's a brief description of FM:  Each sound is created by two operator
 * cells (called "slots" in the Yamaha documentation), a modulator and a
 * carrier.  When FM synthesis was invented, the output value of the
 * modulator affected the frequency of the carrier.  In the Yamaha chips, the
 * modulator output actually affects the phase of the carrier instead of
 * frequency, but this has a similar  effect.
 *
 * Normally the modulator and carrier would probably be connected in series
 * for complex sounds.  For this program, I wanted a pure sine wave, so I
 * connected them in parallel and turned the modulator output down all the
 * way and used just the carrier.
 *
 * Sound Blaster 1.0 - 2.0 cards have one OPL-2 FM synthesis chip at
 * addresses 2x8 and 2x9 (base + 8 and base + 9).  Sound Blaster Pro version
 * 1 cards (CT-1330) achieve stereo FM with two OPL-2 chips, one for each
 * speaker.  The left channel FM chip is at addresses 2x0 and 2x1.  The right
 * is at 2x2 and 2x3.  Addresses 2x8 and 2x9 address both chips
 * simultaneously, thus maintaining compatibility with the monaural Sound
 * Blaster cards.  The OPL-2 contains 18 operator cells which make up the
 * nine 2-operator channels.  Since the CT-1330 SB Pro has two OPL-2 chips,
 * it is therefore capable of generating 9 voices in each speaker.
 *
 * Sound Blaster Pro version 2 (CT-1600) and Sound Blaster 16 cards have one
 * OPL-3 stereo FM chip at addresses 2x0 - 2x3.  The OPL-3 is separated into
 * two "banks."  Ports 2x0 and 2x1 control bank 0, while 2x2 and 2x3 control
 * bank 1.  Each bank can generate nine 2-operator voices.  However, when the
 * OPL-3 is reset, it switches into OPL-2 mode.  It must be put into OPL-3
 * mode to use the voices in bank 1 or the stereo features.  For stereo
 * control, each channel may be sent to the left, the right, or both
 * speakers, controlled by two bits in registers C0H - C8H.
 *
 * The FM chips are controlled through a set of registers.  The following
 * table shows how operator cells and channels are related, and the register
 * offsets to use.
 *
 * FUNCTION  MODULATOR-  -CARRIER--  MODULATOR-  -CARRIER--  MODULATOR-  -CARRIER--
 * OP CELL    1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18
 * CHANNEL    1   2   3   1   2   3   4   5   6   4   5   6   7   8   9   7   8   9
 * OFFSET    00  01  02  03  04  05  08  09  0A  0B  0C  0D  10  11  12  13  14  15
 *
 * An example will make the use of this table clearer:  suppose you want to
 * set the attenuation of both of the operators of channel 4.  The KSL/TOTAL LEVEL
 * registers (which set the attenuation) are 40H - 55H.  The modulator for
 * channel 4 is op cell 7, and the carrier for channel 4 is op cell 10.  The
 * offsets for the modulator and carrier cells are 08H and 0BH, respectively.
 * Therefore, to set the attenuation of the modulator, you would output a
 * value to register 40H + 08H == 48H, and to set the carrier's attenuation,
 * you would output to register 40H + 0BH == 4BH.
 *
 * In this program, I used just channel 1, so the registers I used were 20H,
 * 40H, 60H, etc., and 23H, 43H, 63H, etc.
 *
 * The frequencies of each channel are controlled with a frequency number and
 * a multiplier.  The modulator and carrier of a channel both get the same
 * frequency number, but they may be given different multipliers.  Frequency
 * numbers are programmed in registers A0H - A8H (low 8 bits) and B0H - B8H
 * (high 2 bits).  Those registers control entire channels (2 operators), not
 * individual operator cells.  To turn a note on, the key-on bit in the
 * appropriate channel register is set.  Since these registers deal with
 * channels, you do not use the offsets listed in the table above.  Instead,
 * add (channel-1) to A0H or B0H.  For example, to turn channel 1 on,
 * program the frequency number in registers A0H and B0H, and set the key-on
 * bit to 1 in register B0H.  For channel 3, use registers A2H and B2H.
 *
 * Bits 2 - 4 in registers B0H - B8H are the block (octave) number for the
 * channel.
 *
 * Multipliers for each operator cell are programmed through registers 20H -
 * 35H.  The table below shows what multiple number to program into the
 * register to get the desired multiplier.  The multiple number goes into
 * bits 0 - 3 in the register.  Note that it's a bit strange at the end.
 *
 *   multiple number     multiplier        multiple number     multiplier
 *          0                1/2                   8               8
 *          1                 1                    9               9
 *          2                 2                    10              10
 *          3                 3                    11              10
 *          4                 4                    12              12
 *          5                 5                    13              12
 *          6                 6                    14              15
 *          7                 7                    15              15
 *
 * This equation shows how to calculate the required frequency number (to
 * program into registers A0H - A8H and B0H - B8H) to get the desired
 * frequency:
 *                fn=(long)f * 1048576 / b / m /50000L
 * where f is the frequency in Hz,
 *       b is the block (octave) number between 0 and 7 inclusive, and
 *       m is the multiple number between 0 and 15 inclusive.
 *
 */


#define STEREO         // Define this for SBPro CT-1330 or later card.
#define OPL3           // Also define this for SBPro CT-1600 or later card.


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>

#define KEYON	 0x20     /* key-on bit in regs b0 - b8 */

 /* These are offsets from the base I/O address. */
#define FM       8        /* SB (mono) ports (e.g. 228H and 229H)  */
#define PROFM1   0        /* On CT-1330, this is left OPL-2.  On CT-1600 and */
			  /* later cards, it's OPL-3 bank 0.     */
#define PROFM2   2        /* On CT-1330, this is right OPL-2.  On CT-1600 and */
			  /* later cards, it's OPL-3 bank 1.   */



#ifdef OPL3
  #define LEFT     0x10
  #define RIGHT	   0x20
#endif


#define KEY_UP     72  
#define KEY_DOWN    80
#define ESC       0x1B

#define VGM_HEADER_LEN (0x80)
#define SAMPLE_RATE (44100)

unsigned IOport;        /* Sound Blaster port address  */



void mydelay(unsigned long clocks)
/*
 * "clocks" is clock pulses (at 1.193180 MHz) to elapse, but remember that
 * normally the system timer runs in mode 3, in which it counts down by twos,
 * so delay3(1193180) will only delay half a second.
 *
 *   clocks = time * 2386360
 *
 *     time = clocks / 2386360
 */
{
   unsigned long elapsed=0;
   unsigned int last,next,ncopy,diff;

   /* Read the counter value. */
   outp(0x43,0);                              /* want to read timer 0 */
   last=inp(0x40);                            /* low byte */
   last=~((inp(0x40)<< 8) + last);            /* high byte */

   do {
      /* Read the counter value. */
      outp(0x43,0);                           /* want to read timer 0 */
      next=inp(0x40);                         /* low byte */
      ncopy=next=~((inp(0x40)<< 8) + next);   /* high byte */

      next-=last;      /* this is now number of elapsed clock pulses since last read */

      elapsed += next; /* add to total elapsed clock pulses */
      last=ncopy;
   } while (elapsed<clocks);
}



int base16(char **str, unsigned *val)
/* Takes a double pointer to a string, interprets the characters as a
 * base-16 number, and advances the pointer.
 * Returns 0 if successful, 1 if not.
 */
{
   char c;
   int digit;
   *val = 0;

   while ( **str != ' ') {
      c = toupper(**str);
      if (c >= '0' && c <= '9')
         digit = c - '0';
      else if (c >= 'A' && c <= 'F')
         digit = c - 'A'  + 10;
      else
	 return 1;          /* error in string      */

      *val = *val * 16 + digit;
      (*str)++;
   }
   return 0;
}



int base10(char **str, unsigned *val)
/* Takes a double pointer to a string, interprets the characters as a
 * base-10 number, and advances the pointer.
 * Returns 0 if successful, 1 if not.
 */
{
   char c;
   int digit;
   *val = 0;

   while ( **str != ' ') {
      c = toupper(**str);
      if (c >= '0' && c <= '9')
         digit = c - '0';
      else
	 return 1;          /* error in string    */

      *val = *val * 10 + digit;
      (*str)++;
   }
   return 0;
}



unsigned ReadBlasterEnv(unsigned *port, unsigned *irq, unsigned *dma8,
 unsigned *dma16)
/* Gets the Blaster environment statement and stores the values in the
 * variables whose addresses were passed to it.
 * Returns:
 *   0  if successful
 *   1  if there was an error reading the port address.
 *   2  if there was an error reading the IRQ number.
 *   3  if there was an error reading the 8-bit DMA channel.
 *   4  if there was an error reading the 16-bit DMA channel.
 */
{
   char     *env;
   unsigned val;
   int      digit;

   env = getenv("BLASTER");

   while (*env) {
      switch(toupper( *(env++) )) {
         case 'A':
            if (base16(&env, port))     /*interpret port value as hex */
               return 1;                /* error*/
            break;
         case 'I':
            if (base10(&env, irq))      /* interpret IRQ as decimal*/
               return 2;                /* error*/
            break;
         case 'D':
            if (base10(&env, dma8))     /* 8-bit DMA channel is decimal*/
               return 3;
            break;
         case 'H':
            if (base10(&env, dma16))    /* 16-bit DMA channel is decimal*/
               return 4;
            break;
         default:
            break;
      }
   }

   return 0;
}



void FMoutput(unsigned port, int reg, int val)
/* This outputs a value to a specified FM register at a specified FM port. */
{
   outp(port, reg);
   mydelay(8);          /* need to wait 3.3 microsec */
   outp(port+1, val);
   mydelay(55);         /* need to wait 23 microsec */
}
void Sleep(int time){
int i=0;
	for (i=0;i<43;i++)
	       mydelay(time*50);
	
}


void fm(int reg, int val)
/* This function outputs a value to a specified FM register at the Sound
 * Blaster (mono) port address.
 */
{
   FMoutput(IOport+FM, reg, val);
}


void Profm1(int reg, int val)
/* This function outputs a value to a specified FM register at the Sound
 * Blaster Pro left FM port address (or OPL-3 bank 0).
 */
{
   FMoutput(IOport+PROFM1, reg, val);
}


void Profm2(int reg, int val)
/* This function outputs a value to a specified FM register at the Sound
 * Blaster Pro right FM port address (or OPL-3 bank 1).
 */
{
   FMoutput(IOport+PROFM2, reg, val);
}



float speed = SAMPLE_RATE/900.0f;


long  ld_int(char * p){
   return (p[0]&0xff+(p[1]&0xff)<<8)+((p[2]&0xff)<<16);
}
void OPL3write(char * raw){
	int show=0;
 if (show)	printf("%02X %02X %02X =>",raw[0]&0xff,raw[1]&0xff,raw[2]&0xff);
   
	
	if(raw[0]){
		Profm2(raw[1],raw[2]);
	}else{
		fm(raw[1],raw[2]);
	}
	
}
void OPL3off()
{

     char reset[]={0x5f,0x05,0x00};
     OPL3write(reset);
     reset[0]=0x5e;
     reset[1]=0x01;
     OPL3write(reset);
     reset[1]=0x08;
     OPL3write(reset);

     Sleep(150);

}
void reset()
{
     int add;
     char reset[]={0x5f,0x05,0x01};
     OPL3write(reset);
     reset[1]=0x04;
     reset[2]=0x00;
     OPL3write(reset);

     reset[2]=0x00;

     for(add=0;add<=0xff;add++){
     	reset[1]=add;
     	reset[0]=0x5e;
     	OPL3write(reset);

     	reset[0]=0x5f;
     	OPL3write(reset);

	 }

	Sleep(500);
    OPL3off();
}
void nop(){
	int i=0;
	for(;i<1000;i++);
}

void locateCursor(const int row, const int col){
    printf("%c[%d;%dH",27,row,col);
}

void playFile(const char * vgmfile){
    int wait=0;
    char op[3]={0};
	char key=0;
	char started=0;
	int count=0;
		char vgm_header[VGM_HEADER_LEN]={0};
            FILE * vgm=fopen(vgmfile,"rb");
		printf("playing: %s                       \n",vgmfile);

	    printf("speed:%f\n",speed);

		wait=0;
	    if(vgm!=NULL){
	    	fread(vgm_header,VGM_HEADER_LEN,1,vgm);
	    	printf("data offset:%02X\n",(vgm_header[0x34]&0xff)+0x34);

	    	printf("OPL2:%ld Hz                \n",ld_int(&vgm_header[0x50]));
	    	reset();
	    	if(ld_int(&vgm_header[0x50])) OPL3off();

	    	printf("OPL3:%d Hz                \n",vgm_header[0x5c]+(vgm_header[0x5d]<<8)+((vgm_header[0x5e]&0xff)<<16));
	    	fseek(vgm,(vgm_header[0x34]&0xff)+0x34,SEEK_SET);
              printf("Up/Down : speed ... Esc: Stop  \n");
		printf("Modified by zhblue \n");
	    	started=0;
	    	while(fread(op,3,1,vgm)==1){
			if(kbhit()){
			    		key = getch();
			    		if(key==KEY_UP) speed+=1;
			    		if(key==KEY_DOWN) speed-=1;
			    		if(key==ESC) break;
			    		key=0;
			    		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b speed:%f",speed);
			}	
	    		if(op[0]==0x5e || op[0]==0x5f || op[0]==0x5A ){
	    		   OPL3write(op);
	    		   count++;
	    		   started=1;

	    		}else{

	    		   switch (op[0]){
	    		   		case 0x61:
	    		   			wait=(op[1]&0xff)+((op[2]&0xff)*256);
	    		   			break;
	    		   		case 0x62:
	    		   			wait=735;
	    		   			fseek(vgm,-2,SEEK_CUR);
	    		   			break;
	    		   		case 0x63:
	    		   			wait=882;
	    		   		    fseek(vgm,-2,SEEK_CUR);
	    		   			break;
	    		   		case 0x66:
						    wait=-1;
						    break;
						case 0x70:
						case 0x71:
						case 0x72:
						case 0x73:
						case 0x74:
						case 0x75:
						case 0x76:
						case 0x77:
						case 0x78:
						case 0x79:
						case 0x7a:
						case 0x7b:
						case 0x7c:
						case 0x7d:
						case 0x7e:
						case 0x7f:
	    		   			wait=1+(0xff&op[0]-0x70);
	    		   			fseek(vgm,-2,SEEK_CUR);
	    		   			break;

	    		   		default: wait=0;
				   }
				   if (started && wait>=speed) {

					   	Sleep(wait/speed);

				   }

				}
	    		if(wait<0) break;

			}

		}
		fclose(vgm);
}

void main(int argn,char * argv[])
{
   int i,val1,val2;

   int block,b,m,f,fn;

   unsigned dummy;


   clrscr();

   ReadBlasterEnv(&IOport, &dummy, &dummy, &dummy);

#ifdef STEREO
 #ifdef OPL3
   printf("Program compiled for Sound Blaster Pro ver. 2 (CT-1600) and SB16 cards.\n");
 #else
   printf("Program compiled for Sound Blaster Pro ver. 1 (CT-1330) cards.\n");
 #endif
#else
   printf("Program compiled for Sound Blaster 1.0 - 2.0 cards (monaural).\n");
#endif


   fm(1,0);        /* must initialize this to zero */

#ifdef OPL3
   Profm2(5, 1);  /* set to OPL3 mode, necessary for stereo */
   fm(0xC0,LEFT | RIGHT | 1);     /* set both channels, parallel connection */
#else
   fm(0xC0,               1);     /* parallel connection */
#endif
   if (argn>1)
	playFile(argv[1]);
   else
	playFile("ultima.vgm");
}
