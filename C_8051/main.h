#include <REGX51.H>

#define SDI  P3_0 //Data pin of HC595 connected to P3.0
#define CLK  P3_1 //Clock pin of HC595 connected to P3.1
#define STR  P3_2 //Trigger pin of HC595 connected to P3.3

//To recognize which row is being scaned. It has 8 rows
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

//To make sure only 1 HC works at the time
typedef enum Scanner_status {
    HC138,
		HC595,
    Stable
}Scanner_status;

void RowScanner();
void ColumnScanner();

Scanner_status GlobalScannerStatus;		//Used as status of IC scaner, only 1 IC works at the time, when HC138 works HC595 blocked and the other
unsigned char buffer[32];							//Used as column buffer, it has 32 columns
unsigned char example[8]={0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f};
Row CurrentRow;

//Font
/*
unsigned char letterA[8]={0x1f, 0x24, 0x44, 0x44, 0x7f, 0x00, 0x00, 0x00};
unsigned char letterB[8]={0x7F, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00, 0x00};
unsigned char letterC[8]={0x3e, 0x41, 0x41, 0x41, 0x22, 0x00, 0x00, 0x00};
unsigned char letterD[8]={0x7f, 0x41, 0x41, 0x41, 0x2e, 0x00, 0x00, 0x00};
unsigned char letterE[8]={0x7f, 0x49, 0x49, 0x49, 0x41, 0x00, 0x00, 0x00};

unsigned char letterF[8]={0x7f, 0x48, 0x48, 0x48, 0x40, 0x00, 0x00, 0x00};
unsigned char letterG[8]={0x3e, 0x41, 0x41, 0x45, 0x26, 0x00, 0x00, 0x00};
unsigned char letterH[8]={0x7f, 0x08, 0x08, 0x08, 0x7f, 0x00, 0x00, 0x00};
unsigned char letterI[8]={0x00, 0x41, 0x7f, 0x41, 0x00, 0x00, 0x00, 0x00};
*/

unsigned char letterJ[8]={0x00, 0x02, 0x41, 0x41, 0x7e, 0x00, 0x00, 0x00};
unsigned char letterK[8]={0x7f, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00, 0x00};
unsigned char letterL[8]={0x7f, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00};
unsigned char letterM[8]={0x7f, 0x20, 0x18, 0x20, 0x7f, 0x00, 0x00, 0x00};
unsigned char letterN[8]={0x7f, 0x10, 0x08, 0x04, 0x7f, 0x00, 0x00, 0x00};
unsigned char letterO[8]={0x3e, 0x41, 0x41, 0x41, 0x3e, 0x00, 0x00, 0x00};
/*
unsigned char letterP[8]={0x7f, 0x48, 0x48, 0x48, 0x30, 0x00, 0x00, 0x00};
unsigned char letterQ[8]={0x3c, 0x42, 0x42, 0x42, 0x3D, 0x00, 0x00, 0x00};
unsigned char letterR[8]={0x7f, 0x48, 0x4c, 0x4a, 0x31, 0x00, 0x00, 0x00};
unsigned char letterS[8]={0x32, 0x49, 0x49, 0x49, 0x26, 0x00, 0x00, 0x00};
unsigned char letterT[8]={0x40, 0x40, 0x7f, 0x40, 0x40, 0x00, 0x00, 0x00};
unsigned char letterU[8]={0x7e, 0x01, 0x01, 0x01, 0x7e, 0x00, 0x00, 0x00};
unsigned char letterV[8]={0x7c, 0x02, 0x01, 0x02, 0x7c, 0x00, 0x00, 0x00};
unsigned char letterW[8]={0x7e, 0x01, 0x06, 0x01, 0x7e, 0x00, 0x00, 0x00};
unsigned char letterX[8]={0x63, 0x14, 0x08, 0x14, 0x63, 0x00, 0x00, 0x00};
unsigned char letterY[8]={0x70, 0x08, 0x0f, 0x08, 0x70, 0x00, 0x00, 0x00};
unsigned char letterZ[8]={0x43, 0x45, 0x49, 0x51, 0x43, 0x00, 0x00, 0x00};
*/