#include<pic.h>
__CONFIG (0X20F4);
#define _XTAL_FREQ 4000000
#define lcd PORTB
void lcd_main();
void data(unsigned char by );
void command(unsigned char x );
void disp(unsigned char a[] );
void delay(unsigned int x);
void initialise_reg();
void keypad();
void send_otp();
void gsm(unsigned char x[]);
void otp();
char a=01;
char b=04;	
char x1,x2,x3,x4;


int arr[4];

void main()
{
OSCCON=0x60;
initialise_reg();
lcd_main();

command(0X80);
disp("Welcome");
delay(1000);
command(0XC0);
disp("Security System");
delay(50000);
command(0X01);   	 //clear display
command(0X80);

if(RD2==1)             //send OTP
{	command(0X01);   	 //clear display
	disp("please wait...");
	send_otp();			// OTP function
	delay(20000);
}
else
{
	disp("PRESS BUTTON FOR OTP");
	delay(100000);
	for(int i=0;i<15;i++)
	{	
		command(0X18);
		delay(10000);
	}	
}
command(0X80);
command(0X01);   	 //clear display
disp("Enter Password");

while(1)
{
command(0XC0);

keypad();

if(x1==arr[0])
{
	if(x2==arr[1])
	{
		if(x3==arr[2])
		{
			if(x4==arr[3])
			{
				command(0X01);
				disp("Door Opened :)");
				RC5=1;

			}
		}
	}
}
else
{	command(0x80);
	disp("Try Again");
	RD4=1;
}


	}

}
void initialise_reg()
{
ANSEL=0X00;
ANSELH=0X00;
TRISA=0X07;
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
command(0x0e);

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


void keypad()		//KEYPAD MATRIX
{
int n=0;
int l=-1;

while(n<4)
{
RA3=1;RA4=0;RA5=0;	
		if(RA0==1)
			{
				data('1');
			//	arr[l++]="1";
				while(RA0==1);
				n++;
				delay(100);
			}
		else if(RA1==1)
			{
				data('2');
			//	arr[l++]="2";
				while(RA1==1);
				n++;
				delay(100);
			}
		else if(RA2==1)
			{
				data('3');
			//	arr[l++]="3";
				while(RA2==1);
				n++;
				delay(100);
			}

RA4=1;RA3=0;RA5=0;	
		if(RA0==1)
			{
				data('4');
				while(RA0==1);
				n++;
				delay(100);
			}
		else if(RA1==1)
			{
				data('5');
				while(RA1==1);
				n++;
				delay(100);
			}
		else if(RA2==1)
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
		else if(RA1==1)
			{
				data('8');
				while(RA1==1);
				n++;
				delay(100);
			}
		else if(RA2==1)
			{
				data('9');
				while(RA2==1);
				n++;
				delay(100);
			}
RA5=0;RA3=0;RA4=0;

}
}

void send_otp()
{
TXSTA=0X24;
RCSTA=0X90;
SPBRG=10;

gsm("AT\r\n");
__delay_ms(1000);

gsm("AT+CMGF=1\r\n");
__delay_ms(1000);
gsm("AT+CMGS=\"+918700427871\"\r\n");
__delay_ms(1000);
gsm("Your OTP is:");
__delay_ms(100);

otp();

		TXIF=0;
		TXREG=(char)26;
		while(TXIF==0);	
		__delay_ms(5000);


}

void gsm(unsigned char x[])
{
 	int i=0;
	while(x[i]!= '\0')
	{
		TXIF=0;
		TXREG=x[i];
		while(TXIF==0);	
		i++;
	}
}




void otp()
{

char x1,x2,x3,x4;

a+=0x01;
b+=0x11;

x1=  a%10;
x2= (a/10)%10;
x3=  b%10;
x4= (b/10)%10;
 
		TXIF=0;
		TXREG=x1+48;
		while(TXIF==0);

		TXIF=0;
		TXREG=x2+48;
		while(TXIF==0);	

		TXIF=0;
		TXREG=x3+48;
		while(TXIF==0);	

		TXIF=0;
		TXREG=x4+48;
		while(TXIF==0);	
	
}

