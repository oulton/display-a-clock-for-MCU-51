#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar sshi,sge,fshi,fge,mshi,mge;
uchar num=0,snum=0,fnum=0,mnum=0;
sbit dula=P2^6;
sbit wela=P2^7;
uchar code table[]={0x3f,0x06,0x5b,0x4f,
					0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,
					0x39,0x5e,0x79,0x71};
uchar code tablewela[]={0xff,
						0xfe,0xfd,0xfb,0xf7,
						0xef,0xdf,0xbf,0x7f};
void delay(uint);
void display(uchar ,uchar ,uchar ,uchar ,uchar ,uchar );
void main()
{
	TMOD=0x01;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1)
	{
		display(sshi,sge,fshi,fge,mshi,mge);
	}
}
void display(uchar sshi,uchar sge,uchar fshi,uchar fge,uchar mshi,uchar mge)
{
	dula=1;	   //ËÍÈë¶ÎÑ¡
	P0=table[sshi];
	dula=0;
	P0=0xff; 
	wela=1;    //ËÍÈëÎ»Ñ¡
	P0=tablewela[1];
	wela=0;
	delay(2);

	dula=1;	   //ËÍÈë¶ÎÑ¡
	P0=table[sge];
	dula=0;
	P0=0xff; 
	wela=1;    //ËÍÈëÎ»Ñ¡
	P0=tablewela[2];
	wela=0;
	delay(2);

	dula=1;	   //ËÍÈë¶ÎÑ¡
	P0=0x40;
	dula=0;
	P0=0xff; 
	wela=1;    //ËÍÈëÎ»Ñ¡
	P0=tablewela[3];
	wela=0;
	delay(2);

	dula=1;	   //ËÍÈë¶ÎÑ¡
	P0=table[fshi];
	dula=0;
	P0=0xff; 
	wela=1;    //ËÍÈëÎ»Ñ¡
	P0=tablewela[4];
	wela=0;
	delay(2);

	dula=1;	   //ËÍÈë¶ÎÑ¡
	P0=table[fge];
	dula=0;
	P0=0xff; 
	wela=1;    //ËÍÈëÎ»Ñ¡
	P0=tablewela[5];
	wela=0;
	delay(2);

	dula=1;	   //ËÍÈë¶ÎÑ¡
	P0=0x40;
	dula=0;
	P0=0xff; 
	wela=1;    //ËÍÈëÎ»Ñ¡
	P0=tablewela[6];
	wela=0;
	delay(2);

	dula=1;	   //ËÍÈë¶ÎÑ¡
	P0=table[mshi];
	dula=0;
	P0=0xff; 
	wela=1;    //ËÍÈëÎ»Ñ¡
	P0=tablewela[7];
	wela=0;
	delay(2);

	dula=1;	   //ËÍÈë¶ÎÑ¡
	P0=table[mge];
	dula=0;
	P0=0xff; 
	wela=1;    //ËÍÈëÎ»Ñ¡
	P0=tablewela[8];
	wela=0;
	delay(2);
}
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void T0_timer()interrupt 1
{
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	num++;
	if(num==20)
	{
		num=0;
		mnum++;
		if(mnum==60)
		{
			mnum=0;
			fnum++;
			if(fnum==60)
			{	
				fnum=0;
				snum++;
				if(snum==24)
					snum=0;
			}
		}
		sshi=snum/10;sge=snum%10;
		fshi=fnum/10;fge=fnum%10;
		mshi=mnum/10;mge=mnum%10;
	}		
}
