#include "msp430.h"
#include "stdio.h"
#define DELTA 2
#define DELTA_R 2
#define DELTA_S 20
#define RMS_MIN 20
#define RMS_MAX 1446
#define AMP_MIN 20
#define AMP_MAX 2044
#define U33_MAX 400
#define U33_MIN 300
#define TIMEOUT 30

//functions declare;
void initialize(void);					//функция инициализации
void SetVCoreUp (unsigned int level);
void setport(char num, char data);
char readport(char num);
void initport(char ini);
char measure(char channel, int* reslt, char mask, char timeout);
void setsin(char amp, int freq);
void setsqr(char amp, int freq);
void setvolt(char channel, int vol);
char selftest(int* reslt);
void reset(char vect);
char writeusb(char usb);
char readusb(void);
char fm(int* reslt);
char ver_plis(int* reslt);
int temp(void);
void internal(void);
void external(void);

//variables declare
__no_init char buffer[16], point, send[255], spoint, r1, r2, r4, r5, chan, i;
char mask[12]={0xFF, 0xFF, 0xE5, 0xE5, 0xE5, 0xE5, 0xFF, 0xFF, 0xE5, 0xE5, 0xE5, 0xE5};
__no_init int k, result[4], max, min, sr, ind, r3, r6, r7;
__no_init long rms;

//main function
void main(void)
{
	initialize();
	
  while(1)
	{
		if(LDOPWRCTL & LDOBGVBV)
		{
			PUCTL &= ~PUOUT0;
			external();
		}
		else
		{
			PUCTL |= PUOUT0;
			internal();
		}
		WDTCTL = WDTPW + WDTIS0 + WDTCNTCL;
  }	 	
}

//initialize function
void initialize(void)
{
//stop watchdog timer
WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer

//init ports
	P1DIR=0x00;
	P1OUT=0x00;
		
  P2DIR=0xff;
	
  P3DIR=0xff;
	
	P4DIR=0xFF;
		
  P5DIR=0x30;
	P5SEL=0x0F;
	P5OUT=0x30;
	
	P6DIR=0x00;
	P6SEL=0xFF;
	
//init LDO
  LDOKEYPID=0x9628;
	LDOPWRCTL=LDOONIE | LDOOFFIE | LDOOEN;
	LDOPWRCTL&=~(LDOOFFIFG+LDOONIFG);
	PUCTL = PUOPE + PUOUT0;

//init USART
	
//init CLK & power
	SetVCoreUp (1);
	SetVCoreUp (2);
	SetVCoreUp (3);

	UCSCTL6|=XT2BYPASS;
	UCSCTL5=DIVPA_0 | DIVA_0 | DIVS_0 | DIVM_0;
	UCSCTL4=SELA__XT2CLK | SELS__XT2CLK | SELM__XT2CLK;

	while (UCSCTL7 & XT2OFFG) 
	{
		UCSCTL7 &= ~(XT2OFFG);
		SFRIFG1 &= ~OFIFG;
	}

//init ADC
	REFCTL0=0;
	ADC12CTL0=ADC12REF2_5V | ADC12REFON;
	ADC12CTL1=ADC12SHP | ADC12SSEL1 | ADC12CONSEQ1;
	ADC12CTL2=ADC12RES1 | ADC12REFOUT | ADC12PDIV | ADC12DF;
	ADC12MCTL0=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_0;
	ADC12MCTL1=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_1;
	ADC12MCTL2=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_2;
	ADC12MCTL3=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_3;
	ADC12MCTL4=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_4;
	ADC12MCTL5=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_5;
	ADC12MCTL6=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_6;
	ADC12MCTL7=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_7;
	ADC12MCTL8=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_8;
	ADC12MCTL9=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_9;
	ADC12MCTL10=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_10;
	ADC12MCTL11=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_11;
	ADC12MCTL12=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_12;
	ADC12MCTL13=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_13;
	ADC12MCTL14=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_14;
	ADC12MCTL15=ADC12EOS | ADC12SREF1 | ADC12SREF2 | ADC12INCH_15;

//init timer

//init interrupt
	__bis_SR_register(GIE);

//init plis function
	reset(0x00);

	if(selftest(result)!=0)
		while(1);

//init variables
	point=0;

//start watchdog timer
	WDTCTL = WDTPW + WDTIS0;
	
	PUCTL |= PUOUT1;
	return;
}

//------------------------------------------------------------------------------
void SetVCoreUp (unsigned int level)
{
	PMMCTL0_H = 0xA5;																															// Open PMM registers for write access
	SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;							// Set SVS/SVM high side new level
	SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;																	// Set SVM low side to new level
	
	while ((PMMIFG & SVSMLDLYIFG) == 0);																					// Wait till SVM is settled
	PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);																						// Clear already set flags
	PMMCTL0_L = PMMCOREV0 * level;																								// Set VCore to new level
	
	if ((PMMIFG & SVMLIFG))																												// Wait till new level reached
		while ((PMMIFG & SVMLVLRIFG) == 0);
	
	SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;							// Set SVS/SVM low side to new level
	PMMCTL0_H = 0x00;																															// Lock PMM registers for write access
}

//------------------------------------------------------------------------------
void internal(void)
{
	initport(0x0C);
	if(readport(0)!=r1)
		r1=readport(0);
			
	r2=measure(r1>>4, result, mask[r1>>4], TIMEOUT);
	if(r2)
		PUCTL &= ~PUOUT0;
	else
		PUCTL |= PUOUT0;			
				
	switch(r1&0x0F)
	{
	case 0x01:
		ind=(int)r2;
		break;
	case 0x02:
		ind=result[1];
		break;
	case 0x04:
		ind=result[2];
		break;
	case 0x08:
		ind=result[3];
		break;
	default:
		ind=1234;
	}
			
	setport(2,ind&0x00FF);
	setport(3,ind>>8);
			
	r3++;
	setvolt(0,0xFFFF);
	setvolt(1,0x8000);
	setvolt(2,r3);
	setvolt(3,0xFFFF-r3);
			
	setsqr(255, r3);
	
	setsin(255,r3);
	
	return;
}

//------------------------------------------------------------------------------
void external(void)
{
	r4=readusb();
	if(r4)
		if((r4!=0x0A)&&(r4!=0x0D))
		{
			buffer[point]=r4;
			if(buffer[0]=='*')
				point++;
			point&=0x0F;
		}
		else
		{
			point=0;
			if(buffer[point]!='*')
				goto err;
			else
			{
				point++;
				switch(buffer[point])
				{
					case 'M':
						point++;
						switch(buffer[point])
						{
							case 'C':
								point++;
								if((buffer[point]>='0')&&(buffer[point]<='1')&&(buffer[point+1]>='0')&&(buffer[point+1]<='9'))
								{
									r5=(buffer[point]-0x30)*10 + buffer[point+1] - 0x30;
									if(r5<12)
									{
										r4=measure(r5, result, mask[r5], TIMEOUT);
										if(r5==0)
										{
											result[0]*=15;
											result[1]*=15;
											result[3]*=15;
										}
										if((r5==6)||(r5==7))
										{
											result[0]>>=1;
											result[1]>>=1;
											result[3]>>=1;
										}
										sprintf(send,"CH: %d RMS: %d DC: %d AMP+: %d AMP-: %d VAL: %d\n", r5, result[3], result[2], result[0], result[1], r4);
										goto exit;
									}
									else
										goto err;
								}
								else
									goto err;
							break;
							case 'F':
								fm(result);
								sprintf(send,"CH0: %d CH1: %d CH2: %d CH3: %d\n", result[0], result[1], result[2], result[3]);
								goto exit;
							break;
							case 'S':
								r4=selftest(result);
								sprintf(send,"REF+: %d REF0: %d REF-: %d Ucc: %d VAL: %d\n", result[1], result[0], result[2], result[3]+2952, r4);
								goto exit;
							break;
							case 'T':
								sprintf(send,"TEMP: %d DEG CEL\n", (int)temp());
								goto exit;
							break;
							case 'I':
								point++;
								if((buffer[point]>='0')&&(buffer[point]<='3'))
								{
									r5=buffer[point]-0x30;
									sprintf(send,"PORT%d: %d\n", r5, readport(r5));
								}
								else									
									goto err;
								goto exit;
							break;
							case 'V':
								point++;
								switch(buffer[point])
								{
									case 'M':
										sprintf(send,"Version firmvare MSP430: 1.0.0.0\n");
										goto exit;
									break;
									case 'E':
										ver_plis(result);
										sprintf(send,"Version firmvare EPM1270: %d.%d.%d.%d\n", result[3], result[2], result[1], result[0]);
										goto exit;
									break;
									default:
										goto err;
								}
							break;
							default:
								goto err;
						}	
					break;
					case 'S':
						point++;
						switch(buffer[point])
						{
							case 'Q':
								point++;
								if((buffer[point]>='0')&&(buffer[point]<='9')&&(buffer[point+1]>='0')&&(buffer[point+1]<='9')&&(buffer[point+2]>='0')&&(buffer[point+2]<='9'))
									r6=(buffer[point]-0x30)*100 + (buffer[point+1]-0x30)*10 + buffer[point+2] - 0x30;
								else
									goto err;
								
								point+=3;
								if((buffer[point]>='0')&&(buffer[point]<='9')&&(buffer[point+1]>='0')&&(buffer[point+1]<='9')&&(buffer[point+2]>='0')&&(buffer[point+2]<='9'))
									r7=(buffer[point]-0x30)*100 + (buffer[point+1]-0x30)*10 + buffer[point+2] - 0x30;
								else
									goto err;	
								
								if(r7!=0)
								{
									r7=9216/r7-2;
									r6>>=2;
									setsqr((char)r6, r7);
									sprintf(send,"Set SQR OK. AMP: %d FREQ: %d\n", r6<<2, 9216/(r7+2));
									goto exit;
								}
								else
									goto err;
							break;
							case 'S':
								point++;
								if((buffer[point]>='0')&&(buffer[point]<='9')&&(buffer[point+1]>='0')&&(buffer[point+1]<='9')&&(buffer[point+2]>='0')&&(buffer[point+2]<='9'))
									r6=((buffer[point]-0x30)*100 + (buffer[point+1]-0x30)*10 + buffer[point+2] - 0x30)*23;
								else
									goto err;
								
								point+=3;
								if((buffer[point]>='0')&&(buffer[point]<='9')&&(buffer[point+1]>='0')&&(buffer[point+1]<='9')&&(buffer[point+2]>='0')&&(buffer[point+2]<='9'))
									r7=(buffer[point]-0x30)*100 + (buffer[point+1]-0x30)*10 + buffer[point+2] - 0x30;
								else
									goto err;	
								
								if((r6<(64*255+1))&&(r7>0)&&(r7<801))
								{
									r7=14400/r7-17;
									r6>>=6;
									setsin((char)r6, r7);
									sprintf(send,"Set SIN OK. AMP: %d FREQ: %d\n", (r6<<6)/23, 14400/(r7+17)*10);
									goto exit;
								}
								else
									goto err;										
							break;
							case 'I':
								point++;
								if((buffer[point]>='0')&&(buffer[point]<='3'))
									r4=buffer[point]-0x30;
								else
									goto err;
								point++;
								if((buffer[point]>='0')&&(buffer[point]<='2')&&(buffer[point+1]>='0')&&(buffer[point+1]<='9')&&(buffer[point+2]>='0')&&(buffer[point+2]<='9'))
									r6=(buffer[point]-0x30)*100 + (buffer[point+1]-0x30)*10 + buffer[point+2] - 0x30;
								else									
									goto err;
								if(r6<256)
								{
									setport(r4, (char)r6);
									sprintf(send,"Set PORT%d OK\n", r4);
									goto exit;
								}
								else
									goto err;	
							break;
							case 'D':
								point++;
								if((buffer[point]>='0')&&(buffer[point]<='1')&&(buffer[point+1]>='0')&&(buffer[point+1]<='9'))
									r4=(buffer[point]-0x30)*10 + buffer[point+1]-0x30;
								else
									goto err;
								
								if(r4<16)
								{
									initport(r4);
									sprintf(send,"Set port direction %d OK\n", r4);
									goto exit;
								}
								else
									goto err;	
							break;
							case 'V':
								point++;
								if((buffer[point]>='0')&&(buffer[point]<='3'))
									r4=buffer[point]-0x30;
								else
									goto err;
								point++;
								if((buffer[point]>='0')&&(buffer[point]<='9')&&(buffer[point+1]>='0')&&(buffer[point+1]<='9')&&(buffer[point+2]>='0')&&(buffer[point+2]<='9')&&(buffer[point+3]>='0')&&(buffer[point+3]<='9'))
									r6=(buffer[point]-0x30)*1000 + (buffer[point+1]-0x30)*100 + (buffer[point+2] - 0x30)*10 + buffer[point+3] - 0x30;
								else									
									goto err;
								if(r6<3277)
								{
									setport(r4, r6*20);
									sprintf(send,"Set DAC%d OK\n", r4);
									goto exit;
								}
								else
									goto err;	
							break;
							default:
								goto err;
						}
					break;
					case 'R':
						point++;
						switch(buffer[point])
						{
							case 'U':
								reset(0xFE);
								sprintf(send,"USB reset OK\n");
								goto exit;
							break;
							case 'D':
								reset(0xFD);
								sprintf(send,"DACs reset OK\n");
								goto exit;
							break;
							case 'S':
								reset(0xFB);
								sprintf(send,"SIN reset OK\n");
								goto exit;
							break;
							case 'I':
								reset(0xF7);
								sprintf(send,"SPI reset OK\n");
								goto exit;
							break;
							default:
								goto err;
						}
					break;
					case '?':
						sprintf(send,"Commands:\n*-[necessary]\n\tM-measure\n\t\tS-selftest\n\t\tC-ADC\n\t\tF-frequency\n\t\tT-temperature\n\t\tI-I/O port\n\t\tV-version\n\tS-set\n\t\tI-I/O port\n\t\tS-sin\n\t\tQ-square\n\t\tV-volt\n\tR-reset\n\t\tU-USB\n\t\tD-DACS\n\t\tS-sin\n\t\tI-SPI\n\t?-help\n");
					goto exit;
					break;
					default:
						goto err;
				}
			}	
err:
			sprintf(send,"Command error character %d\n", point+1);
	
			exit:
			while(point!=0)
				buffer[point--]=0;
			spoint=0;
			
			while(send[spoint]!=0x00)
			{
				writeusb(send[spoint]);
				spoint++;
			}	
		}
	return;
}

//------------------------------------------------------------------------------
void setport(char num, char data)
{
	P2OUT=num+1;
	P4OUT=data;
	P5OUT&=0xEF;
	P5OUT|=0x10;
	return;
}

//------------------------------------------------------------------------------
char readport(char num)
{
	char read;
	
	P4DIR=0x00;
	P2OUT=num+1;
	P5OUT&=0xDF;
	read=P4IN;
	P5OUT|=0x20;
	P4DIR=0xFF;
	return read;
}

//------------------------------------------------------------------------------
void initport(char ini)
{
	P2OUT=5;
	P4OUT=ini;	
	P5OUT&=0xEF;
	P5OUT|=0x10;
	return;
}

//------------------------------------------------------------------------------
char measure(char channel, int* reslt, char mask, char timeout)
{
	char c, val=0xFF;
	int ampp, ampm, mino, maxo, rmso, delta;
	long rmst, div, rslt;

//PUCTL &= 0xFD;
	chan=channel;
	ADC12CTL1&=0x0FFF;	
	ADC12CTL1|=(int)chan<<12;
	ADC12IFG=0x0000;
	ADC12IE=0x0001<<chan;
	ADC12CTL0=0x7700 | ADC12MSC | ADC12REF2_5V | ADC12REFON | ADC12ON | ADC12ENC | ADC12SC;

	for(c=0;(c<timeout)&&((val&mask)!=0);c++)
	{
		k=0;
		max=0x8000;
		min=0x7FFF;
		rms=0;

		while(k<512);

		rmst=rms>>9;
		delta=maxo;	
	//mino+=(min-mino)>>1;
	//maxo+=(max-maxo)>>1;
		mino=(min<0)?((min>>4)|0xF000):(min>>4);
		maxo=(max<0)?((max>>4)|0xF000):(max>>4);
		delta-=maxo;
	
		if((delta<DELTA)&&(delta>-DELTA))
			val&=0xBF;
		else
			val|=0x40;

		delta=sr;
		sr=(maxo+mino)/2;
		delta-=sr;

		if((delta<DELTA)&&(delta>-DELTA))
			val&=0xDF;
		else
			val|=0x20;

		if((sr<DELTA_S)&&(sr>-DELTA_S))
			val&=0xFD;
		else
			val|=0x02;

		ampp=maxo-sr;
		ampm=sr-mino;

		delta=ampp-ampm;
		if((delta<DELTA)&&(delta>-DELTA))
			val&=0xFE;
		else
			val|=0x01;

		if((ampp<AMP_MAX)&&(ampm<AMP_MAX))
			val&=0xFB;
		else
			val|=0x04;

		if((ampp>AMP_MIN)&&(ampm>AMP_MIN))
			val&=0xF7;
		else
			val|=0x08;

		div=rmst;
		rslt=rmst;

		while(rmst)
		{
			div=(rmst/div+div)>>1;
			if(rslt>div)
				rslt=div;
			else
				goto exit;
		}

exit:
		delta=rmso;	
	//rmso+=((int)rslt-rmso)>>2;
		rmso=(int)rslt;
		delta-=rmso;

		if((delta<DELTA_R)&&(delta>-DELTA_R))
			val&=0x7F;
		else
			val|=0x80;

		if((rmso>RMS_MIN)&&(rmso<RMS_MAX))
			val&=0xEF;
		else
			val|=0x10;
	}
	if(ampp>AMP_MIN)
		reslt[0]=ampp;
	else
		reslt[0]=0;
	if(ampm>AMP_MIN)
		reslt[1]=ampm;
	else
		reslt[1]=0;
	if((sr<DELTA_S)&&(sr>-DELTA_S))
		reslt[2]=0;
	else
		reslt[2]=sr;
	if(rmso>RMS_MIN)	
		reslt[3]=rmso;
	else
		reslt[3]=0;

	ADC12IE=0;
	ADC12IFG=0;
	ADC12CTL0&=~(ADC12ENC + ADC12SC);
	ADC12MEM[chan&0x0F]=0;

//PUCTL |= 0x02;
	return val&mask;
}

//------------------------------------------------------------------------------
void setsin(char amp, int freq)
{
	P2OUT=17;
	P4OUT=(char)(freq&0x00FF);
	P5OUT&=0xEF;
	P5OUT|=0x10;
	
	P2OUT=18;
	P4OUT=(char)(freq>>8);
	P5OUT&=0xEF;
	P5OUT|=0x10;
		
	P2OUT=15;
	P4OUT=amp;
	P5OUT&=0xEF;
	P5OUT|=0x10;

	return;
}

//------------------------------------------------------------------------------
void setsqr(char amp, int freq)
{
	P2OUT=19;
	P4OUT=(char)(freq&0x00FF);
	P5OUT&=0xEF;
	P5OUT|=0x10;
	
	P2OUT=20;
	P4OUT=(char)(freq>>8);
	P5OUT&=0xEF;
	P5OUT|=0x10;
		
	P2OUT=16;
	P4OUT=amp;
	P5OUT&=0xEF;
	P5OUT|=0x10;
	
	return;
}

//------------------------------------------------------------------------------
void setvolt(char channel, int vol)
{
	P2OUT=(channel<<1)+7;
	P4OUT=(char)(vol&0x00FF);
	P5OUT&=0xEF;
	P5OUT|=0x10;
	
	P2OUT=(channel<<1)+8;
	P4OUT=(char)(vol>>8);
	P5OUT&=0xEF;
	P5OUT|=0x10;
	
	return;
}

//------------------------------------------------------------------------------
char selftest(int* reslt)
{
	int result[4];
	char rv=0x0F;
	
	measure(5, result, mask[5], TIMEOUT);
	reslt[0]=result[2];
	if((result[2]<DELTA_S)&&(result[2]>-DELTA_S))
		rv&=0xF7;
	else
		rv|=0x08;
	
	measure(8, result, mask[8], TIMEOUT);
	reslt[1]=result[2];
	if(result[2]>AMP_MAX)
		rv&=0xFB;
	else
		rv|=0x04;
	
	measure(9, result, mask[9], TIMEOUT);
	reslt[2]=result[2];
	if(result[2]<-AMP_MAX)
		rv&=0xFD;
	else
		rv|=0x02;
	
	measure(11, result, mask[11], TIMEOUT);
	reslt[3]=result[2];
	if((result[2]<U33_MAX)&&(result[2]>U33_MIN))
		rv&=0xFE;
	else
		rv|=0x01;
	
	return rv;
}

//------------------------------------------------------------------------------
char ver_plis(int* reslt)
{
	P4DIR=0x00;
	
	P2OUT=251;
	P5OUT&=0xDF;
	reslt[0]=P4IN;
	P5OUT|=0x20;
	
	P2OUT=252;
	P5OUT&=0xDF;
	reslt[1]=P4IN;
	P5OUT|=0x20;
	
	P2OUT=253;
	P5OUT&=0xDF;
	reslt[2]=P4IN;
	P5OUT|=0x20;
	
	P2OUT=254;
	P5OUT&=0xDF;
	reslt[3]=P4IN;
	P5OUT|=0x20;
	
	P4DIR=0xFF;
	return 0;
}

//------------------------------------------------------------------------------
int temp(void)
{
	int result[4];
	
	if(measure(10, result, mask[10], TIMEOUT))
		return -200;
	else
		return (result[2]+1368)>>2;
}

//------------------------------------------------------------------------------
char fm(int* reslt)
{
	char t1, t2;
	
	P4DIR=0x00;
	
	P2OUT=21;
	P5OUT&=0xDF;
	t1=P4IN;
	P5OUT|=0x20;
	
	P2OUT=22;
	P5OUT&=0xDF;
	t2=P4IN;
	P5OUT|=0x20;
	reslt[0]=(((int)t2)<<8)|t1;
	
	P2OUT=23;
	P5OUT&=0xDF;
	t1=P4IN;
	P5OUT|=0x20;
	
	P2OUT=24;
	P5OUT&=0xDF;
	t2=P4IN;
	P5OUT|=0x20;
	reslt[1]=(((int)t2)<<8)|t1;
	
	P2OUT=25;
	P5OUT&=0xDF;
	t1=P4IN;
	P5OUT|=0x20;
	
	P2OUT=26;
	P5OUT&=0xDF;
	t2=P4IN;
	P5OUT|=0x20;
	reslt[3]=(((int)t2)<<8)|t1;
	
	P2OUT=27;
	P5OUT&=0xDF;
	t1=P4IN;
	P5OUT|=0x20;
	
	P2OUT=28;
	P5OUT&=0xDF;
	t2=P4IN;
	P5OUT|=0x20;
	reslt[3]=(((int)t2)<<8)|t1;
	
	P4DIR=0xFF;
	return 0;
}

//------------------------------------------------------------------------------
void reset(char vect)
{
	P2OUT=0;
	P4OUT=vect;
	P5OUT&=0xEF;
	P5OUT|=0x10;
	
	__delay_cycles(10);
	
	P4OUT=0xFF;
	P5OUT&=0xEF;
	P5OUT|=0x10;
	
	return;
}

//------------------------------------------------------------------------------
char writeusb(char usb)
{
	char rv;
	
	P4DIR=0x00;
	P2OUT=255;
	P5OUT&=0xDF;
	rv=P4IN;
	P5OUT|=0x20;
	P4DIR=0xFF;
	P2OUT=6;
	
	if(rv&0x04)
	{
		P4OUT=usb;
		P5OUT&=0xEF;
		P5OUT|=0x10;
		rv=0;
	}
	else
		rv=1;
	
	return rv;
}

//------------------------------------------------------------------------------
char readusb(void)
{
	char rv;
	
	P4DIR=0x00;
	P2OUT=255;
	P5OUT&=0xDF;
	rv=P4IN;
	P5OUT|=0x20;

	if(rv&0x08)
	{
		P2OUT=6;
		P5OUT&=0xDF;
		rv=P4IN;
		P5OUT|=0x20;
	}
	else
		rv=0;
	
	P4DIR=0xFF;
	return rv;
}

//------------------------------------------------------------------------------
#pragma vector=ADC12_VECTOR
__interrupt void adc12(void)
{
	int adc=ADC12MEM[chan&0x0F];

//PUCTL &= 0xFD;
	rms+=((long)adc*(long)adc)>>8;

	if(adc>max)
		max=adc;

	if(adc<min)
		min=adc;

	k++;
//PUCTL |= 0x02;
	return;
}

//------------------------------------------------------------------------------
#pragma vector=LDO_PWR_VECTOR
__interrupt void ldo(void)
{
	LDOPWRCTL&=~(LDOOFFIFG+LDOONIFG);

	PMMCTL0|=PMMSWPOR;
//WDTCTL=WDTPW | WDTIS__64;
	return;
}

//------------------------------------------------------------------------------