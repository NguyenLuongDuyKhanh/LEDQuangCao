#include "main.h"

void main (void)
{
	int i;
	for(i=0;i<8;i++)
	{
		buffer[i] = letterJ[i];
	}
	for(i=0;i<8;i++)
	{
		buffer[i+8] = letterK[i];
	}
	for(i=0;i<8;i++)
	{
		buffer[i+16] = letterL[i];
	}
	for(i=0;i<8;i++)
	{
		buffer[i+24] = letterM[i];
	}
	
	GlobalScannerStatus = Stable;
	CurrentRow = R1;
	P2 = 0x01;
	P3 = 0x00;

	
	while(1)
	{
		if(Stable == GlobalScannerStatus)
		{
			RowScanner();
		}
		if(Stable == GlobalScannerStatus)
		{
			ColumnScanner();
		}
	}
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

void ColumnScanner()
{
	
	int column_number;
	unsigned char temp;
	
	GlobalScannerStatus = HC595;

	for(column_number=31;column_number>=0;column_number--)
	{
		temp = buffer[column_number]<<CurrentRow;
		SDI=temp&0x80;
		CLK=0;
		CLK=1;
	}
	STR=0; 
	STR=1;
	P2=CurrentRow;
	
	GlobalScannerStatus = Stable;
}