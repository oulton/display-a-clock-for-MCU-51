#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar num=0,num1=0,shi=23,fen=59,miao=55;
sbit dula=P2^6;
sbit wela=P2^7;
sbit S2=P3^0;	  //按键按下 定时器停止计时;
sbit Miao=P3^3;	  //Miao加1;
sbit Fen=P3^2;	  //Fen加1;
sbit Shi=P3^1;	  //Shi加1;
sbit beep=P2^3;
uint countS2=0;     //用于计数S2按了几下
uchar code table[]={0x3f,0x06,0x5b,0x4f,
		   			0x66,0x6d,0x7d,0x07,
		    		0x7f,0x6f,0x77,0x7c,
	            	0x39,0x5e,0x79,0x71};
uchar code tablewela[]={0xff,
						0xfe,0xfd,0xfb,0xf7,
						0xef,0xdf,0xbf,0x7f};
void init();
void delay(uint);
void keyscan();
void display(uchar ,uchar ,uchar ,uchar ,uchar ,uchar );
//void is_int_time(uchar ,uchar );
void main()
{
	init();
	while(1)
	{
		keyscan();		
	//	is_int_time(fen,miao);
		display(shi/10,shi%10,fen/10,fen%10,miao/10,miao%10);
	}
}
void init()
{
	TMOD=0x11;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	TH1=(65536-45872)/256;
	TL1=(65536-45872)%256;
	EA=1;
	ET0=1;
	ET1=1;
	TR0=1;
	TR1=1;
}
/*
void is_int_time(uchar fen,uchar miao)
{
	if(fen==0&&miao==0)
	{
		beep=0;
	}
	else
	{
		beep=1;
	}	
}
*/
void keyscan()
{
	if(countS2==0)
	{
		if(S2==0)
		{
			delay(3);
			if(S2==0)
			{
				while(!S2)
				{display(shi/10,shi%10,fen/10,fen%10,miao/10,miao%10);}
				TR0=0;
				countS2++;
			}
		}
	}
	if(countS2==1)
	{
		if(S2==0)
		{
			delay(3);
			if(S2==0)
			{
				while(!S2)
				{display(shi/10,shi%10,fen/10,fen%10,miao/10,miao%10);}
				TR0=1;
				countS2=0;
			}
		}
		if(Miao==0)
		{
			delay(3);
			if(Miao==0)
			{
				while(!Miao)
				{display(shi/10,shi%10,fen/10,fen%10,miao/10,miao%10);}
				miao++;
				if(miao==60)
					miao=0;
				display(shi/10,shi%10,fen/10,fen%10,miao/10,miao%10);
			}
		}
		if(Fen==0)
		{
			delay(3);
			if(Fen==0)
			{
				while(!Fen)
				{display(shi/10,shi%10,fen/10,fen%10,miao/10,miao%10);}
				fen++;
				if(fen==60)
					fen=0;
				display(shi/10,shi%10,fen/10,fen%10,miao/10,miao%10);
			}
		}
		if(Shi==0)
		{
			delay(3);
			if(Shi==0)
			{
				while(!Shi)
				{display(shi/10,shi%10,fen/10,fen%10,miao/10,miao%10);}
				shi++;
				if(shi==24)
					shi=0;
				display(shi/10,shi%10,fen/10,fen%10,miao/10,miao%10);
			}
		}
	}
}
void display(uchar sshi,uchar sge,uchar fshi,uchar fge,uchar mshi,uchar mge)
{
	dula=1;	   
	P0=table[sshi];
	dula=0;
	P0=0xff; 
	wela=1;    
	P0=tablewela[1];
	wela=0;
	delay(2);

	dula=1;	   
	P0=table[sge];
	dula=0;
	P0=0xff; 
	wela=1;    
	P0=tablewela[2];
	wela=0;
	delay(2);

	dula=1;	   
	P0=0x40;
	dula=0;
	P0=0xff; 
	wela=1;    
	P0=tablewela[3];
	wela=0;
	delay(2);

	dula=1;	   
	P0=table[fshi];
	dula=0;
	P0=0xff; 
	wela=1;    
	P0=tablewela[4];
	wela=0;
	delay(2);

	dula=1;	   
	P0=table[fge];
	dula=0;
	P0=0xff; 
	wela=1;    
	P0=tablewela[5];
	wela=0;
	delay(2);

	dula=1;	  
	P0=0x40;
	dula=0;
	P0=0xff; 
	wela=1;    
	P0=tablewela[6];
	wela=0;
	delay(2);

	dula=1;	   
	P0=table[mshi];
	dula=0;
	P0=0xff; 
	wela=1;    
	P0=tablewela[7];
	wela=0;
	delay(2);

	dula=1;	   
	P0=table[mge];
	dula=0;
	P0=0xff; 
	wela=1;    
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
			miao++;
			if(miao==60)
			{
				miao=0;
				fen++;
				if(fen==60)
				{	
					fen=0;
					shi++;
					if(shi==24)
						shi=0;
				}
			}
		}			
}
void T1_timer()interrupt 3
{
	TH1=(65536-45872)/256;
	TL1=(65536-45872)%256;
	num1++;
	if(num1==10)
	{
		num1=0;
		if(fen==0&&miao==0)
			beep=0;
		else
			beep=1;
	}
	if(fen!=0||miao!=0)
		beep=1;
}