//#include<reg52.h>
#include <REGX51.H>
//#include <main.c>

typedef enum Row {
    R1,
    R2,
    R3,
    R4,
		R5,
		R6,
		R7,
		R8,
		None,
}Row;

typedef enum Scanner_status {
    HC138,
		HC595,
    Stable
}Scanner_status;

#define SDI  P3_0 //Chan 14 data
#define CLK  P3_1 //Chan 11 clock
#define STR  P3_2 //Chan 12 chot



unsigned char i;
//unsigned char ma[10]={0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x00}; //Mang LED
unsigned char ma[10]={0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x00}; //Mang LED



Scanner_status GlobalScannerStatus;

//char example[8]={0B01111111b, 01001001b, 01001001b, 01001001b  ,00110110b , 0b, 0b, 0b };

unsigned char example1[8]={0x7F,0x49, 0x49, 0x49  ,0x36 , 0x0,0x0,0x0}; //B
unsigned char example2[8]={0x1f  , 0x24  , 0x44  , 0x44  , 0x7f , 0x0,0x0,0x0 }; //A
unsigned char example3[8]={0x7f  , 0x41  , 0x41  , 0x41  , 0x2e , 0x00,0x00,0x00 };//D
//unsigned char example[8]={0x0f  , 0x0f  , 0x0f  , 0x0f  , 0x0f , 0x0f,0x0f,0x0f };
//unsigned char example[8]={0xff  , 0xff  , 0xff  , 0xff  , 0xff , 0xff,0xff,0xff };
void delay_ms(unsigned int);
void RowScanner();
void ColumnScanner();
void truyen(unsigned char b1);
void delay(unsigned char time);
Row CurrentRow;

void main (void)
{
	CurrentRow = R1;
	P2 = 0x01;
	P3 = 0x00;
	//TMOD=0x01;    //Khoi tao timer 0 che do 16bit
	GlobalScannerStatus = Stable;
	while(1)
	{
		/*
		if(Stable == GlobalScannerStatus)
		{
			RowScanner();
			P2=CurrentRow;
		}
		*/
		if(Stable == GlobalScannerStatus)
		{
			ColumnScanner();
		}
		//delay_ms(1);
		/*
		    for(i=0;i<10;i++){      //Truyen 3 du lieu khac nhau vao 3 ic
        truyen(0xff,ma[i],ma[9-i]);    //Truyen du lieu vao 3 IC
        delay(5);
        truyen(0x00,ma[i-1],ma[9-i]);
        delay(5);
    }
		*/
	}
}

void delay_ms(unsigned int t)
{
		unsigned int i,j;
		for(i=0;i<t;i++)
		for(j=0;j<500;j++);
		//for(j=0;j<1275;j++);
}

void RowScanner()
{
	GlobalScannerStatus = HC138;
	
	if(CurrentRow==R8)
		{
			CurrentRow=R1;
		}else CurrentRow++;
	GlobalScannerStatus = Stable;
}
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

void ColumnScanner()
{
	
	int column_number;
	int row_number;
	unsigned char temp;
	GlobalScannerStatus = HC595;
	for(row_number=0;row_number<8;row_number++)
	{
	for(column_number=7;column_number>=0;column_number--)
	{
		temp = example1[column_number]<<row_number;
		SDI=temp&0x80;
		CLK=0;
		CLK=1;
	}
	
		for(column_number=7;column_number>=0;column_number--)
	{
		temp = example2[column_number]<<row_number;
		SDI=temp&0x80;
		CLK=0;
		CLK=1;
	}
	
		for(column_number=7;column_number>=0;column_number--)
	{
		temp = example3[column_number]<<row_number;
		SDI=temp&0x80;
		CLK=0;
		CLK=1;
	}
	
		for(column_number=7;column_number>=0;column_number--)
	{
		temp = example1[column_number]<<row_number;
		SDI=temp&0x80;
		CLK=0;
		CLK=1;
	}
	STR=0; STR=1; //Chot hien thi du lieu
	P2=row_number;
	}
	GlobalScannerStatus = Stable;
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
		Q=b1;
		for(i=0;i<8;i++)
		{
			SDI=Q&0x80;
			CLK=0;
			CLK=1;
			Q<<=1;
		} //ic 1
		delay(5);
    STR=0; 
		STR=1; //Chot hien thi du lieu
}
