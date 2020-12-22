//#include<reg52.h>
#include <REGX51.H>
typedef enum Row {
    R1,
    R2,
    R3,
    R4,
		R5,
		R6,
		R7,
		R8
}Row;

#define SDI  P3_0 //Chan 14 data
#define CLK  P3_1 //Chan 11 clock
#define STR  P3_2 //Chan 12 chot



unsigned char i;
//unsigned char ma[10]={0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x00}; //Mang LED
unsigned char ma[10]={0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x00}; //Mang LED
void delay(unsigned char time){ //Chuong trinh tao tre 50ms
    unsigned char t;
    for(t=0;t<time;t++){
        TH0=0x3c;
        TL0=0xb0;
        TR0=1;
        while(!TF0);
        TF0=TR0=0;
    }
}
void truyen(unsigned char b1){
/*Chuong trinh truyen du lieu vao 3 IC 74HC595
Cac ban co the mo rong them bao nhieu IC tuy thich
bang cach them code theo mau cua chuong trinh goc
*/
    unsigned char i,Q;
    //Q=b3; for(i=0;i<8;i++){SDI=Q&0x80;CLK=0;CLK=1;Q<<=1;} //ic 3
    //Q=b2; for(i=0;i<8;i++){SDI=Q&0x80;CLK=0;CLK=1;Q<<=1;} //ic 2
    //Q=b1; 
	Q=0xff;
		for(i=0;i<8;i++)
		{
			SDI=Q&0x80;
			CLK=0;
			CLK=1;
			Q<<=1;
		} //ic 1
		delay(5);
    STR=0; STR=1; //Chot hien thi du lieu
		//P3 &= ~(1<<STR);
		//P3 |=
}

unsigned int pinMatrix [8][3] = {
  {0,0,0},
  {1,0,0},
  {0,1,0},
  {1,1,0},
  {0,0,1},
  {1,0,1},
  {0,1,1},
  {1,1,1}
};

void delay_ms(unsigned int);
void RowScaner();

Row CurrentRow = R1;
void main (void)
{
	int i = 0;
	int a = 1000;
	P2 = 0x00;
	P3 = 0x00;
	TMOD=0x01;    //Khoi tao timer 0 che do 16bit
	truyen(0xff); 
	while(1)
	{
		/*
		for (i=0;i<8;i++)
		{
			P2=i;
			delay_ms(100);
		}
		*/
		/*
		switch(CurrentRow)
		{
			case R1:
				P2=R1;
				break
			case R2:
			case R3:
			case R4:
			case R5:
			case R6:
			case R7:
			case R8:
		}*/
		//P2=CurrentRow;
		//RowScaner();
		/*
		    for(i=0;i<10;i++){      //Truyen 3 du lieu khac nhau vao 3 ic
        truyen(0xff,ma[i],ma[9-i]);    //Truyen du lieu vao 3 IC
        delay(5);
        truyen(0x00,ma[i-1],ma[9-i]);
        delay(5);
    }
		*/
		truyen(0xff); 
		delay(5);
	}
}

void delay_ms(unsigned int t)
{
		unsigned int i,j;
		for(i=0;i<t;i++)
		for(j=0;j<1275;j++);
}

void RowScaner()
{
	delay_ms(1);
	CurrentRow++;
	if(CurrentRow==8)
		{
			CurrentRow=R1;
		}
}
