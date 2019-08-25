#include<pic.h>
//__CONFIG (0X20F4);
//   #define _XTAL_FREQ 4000000
#define lcd PORTB
void lcd_main();
void data(unsigned char by );
void command(unsigned char x );
void disp(unsigned char a[] );
void delay(unsigned int x);
void initialise_reg();

void main()
{
OSCCON=0x60;
initialise_reg();
lcd_main();
while(1)
{
int n;

RA3=1;RA4=0;RA5=0;	
		if(RA0==1)
			{
				data('1');
				while(RA0=1);
				n++;
				delay(100);
			}
		if(RA1==1)
			{
				data('2');
				while(RA1=1);
				n++;
				delay(100);
			}
		if(RA2==1)
			{
				data('3');
				while(RA2=1);
				n++;
				delay(100);
			}

RA4=1;RA3=0;RA5=0;	
		if(RA0==1)
			{
				disp('4');
				while(RA0==1);
				n++;
				delay(100);
			}
		 if(RA1==1)
			{
				data('5');
				while(RA1==1);
				n++;
				delay(100);
			}
		 if(RA2==1)
			{
				data('6');
				while(RA2==1);
				n++;
				delay(100);
			}
RA5=1;RA3=0;RA4=0;	
		if(RA0==1)
			{
				data('7');
				while(RA0==1);
				n++;
				delay(100);
			}
		if(RA1==1)
			{
				data('8');
				while(RA1==1);
				n++;
				delay(100);
			}
		if(RA2==1)
			{
				data('9');
				while(RA2==1);
				n++;
				delay(100);
			}
}
}

void initialise_reg()
{
ANSEL=0X00;
ANSELH=0X00;
TRISA=0b00000111;
PORTA=0X00;
TRISB=0X00;
PORTB=0X00;
TRISC=0X87;
PORTC=0X00;
TRISD=0X00;
PORTD=0X00;
TRISE=0X00;
PORTE=0X00;

}


void lcd_main()
{
command(0x38);
command(0x01);
command(0x0C);

}

void data(unsigned char by)
{
lcd=by;
RD6=1;
RD7=1;
delay(50);
RD7=0;
delay(100);
}

void command(unsigned char x)
{
lcd=x;
RD6=0;
RD7=1;
delay(50);
RD7=0;
delay(100);
}

void disp(unsigned char ch[])
{
int i=0;
while(ch[i]!='\0')
	{
		data(ch[i]);
		i++;
	}
}


void delay(unsigned int x)
{
while(x--);
}
