#include<pic.h>
//__CONFIG (0x20f4);
#define _XTAL_FREQ 4000000
#define lcd PORTB
void lcd_main();
void data(unsigned char by);
void command(unsigned char x);
void disp(unsigned char ch[]);
void delay(unsigned int x);
void initialise_reg();

void main()
{
OSCCON=0X60;
initialise_reg();
lcd_main();
while(1)
{
command(0X80);
disp("WEFFak");
command(0X80);
disp("sSecurity ");
delay(20000);

}
}
void initialise_reg()
{
ANSEL=ANSELH=0X00;
TRISA=0X07;
PORTA=0X00;
TRISB=0x00;
PORTB=0x00;
TRISC=0X07;
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
command(0x0e);

}

void data(unsigned char by)
{
lcd=by;
RD6=1;
RD7=0;
delay(150);
RD7=1;
delay(250);
}

void command(unsigned char x)
{
lcd=x;
RD6=0;
RD7=0;
delay(150);
RD7=1;
delay(250);
}


void disp(unsigned char *ch)
{
while(*ch)
{
data(*ch++);
}
}


void delay(unsigned int x)
{
while(x--);
}
