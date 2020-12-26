#include "main.h"

void main (void)
{
	//Initialize row buffer
	int i;
	for(i=0;i<8;i++) //Add first charater
	{
		buffer[i] = letterJ[i];
	}
	for(i=0;i<8;i++) //Add second charater
	{
		buffer[i+8] = letterK[i];
	}
	for(i=0;i<8;i++) //Add third charater
	{
		buffer[i+16] = letterL[i];
	}
	for(i=0;i<8;i++) //Add fourth charater
	{
		buffer[i+24] = letterM[i];
	}
	
	//Initialize status, when status is Stable it means there is no IC is working
	GlobalScannerStatus = Stable;
	//Initialize the first row is being scaned
	CurrentRow = R1;
	//Initialize ouptut status P2 and P3.
	P2 = 0x00;
	P3 = 0x00;

	
	while(1)
	{
		if(Stable == GlobalScannerStatus) //Verify HC595 isn't working then HC138 can works
		{
			RowScanner();
		}
		if(Stable == GlobalScannerStatus) //Verify HC138 isn't working then HC595 can works
		{
			ColumnScanner();
		}
	}
}

void RowScanner()
{
	GlobalScannerStatus = HC138; //It means HC138 is working, the status isn't Stable then HC595 cannot work
	
	if(CurrentRow==R8) //Reset to the first row
		{
			CurrentRow=R1;
		}else CurrentRow++;
	GlobalScannerStatus = Stable; //Release status to stable
}

void ColumnScanner()
{
	
	int column_number;
	unsigned char temp;
	
	GlobalScannerStatus = HC595; //It means HC595 is working, the status isn't Stable then HC138 cannot work

	for(column_number=31;column_number>=0;column_number--) //Scan 32 columns
	{
		temp = buffer[column_number]<<CurrentRow; //Push data to HC595 via data pin and clock pin
		SDI=temp&0x80;
		CLK=0;
		CLK=1;
	}
	STR=0; //Trigger output by toggle STR pin
	STR=1;
	P2=CurrentRow;//Update P2 with CurrentRow variable, which is updated in RowScanner function
	
	GlobalScannerStatus = Stable; //Release status to stable
}