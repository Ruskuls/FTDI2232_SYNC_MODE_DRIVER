#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../ftd2xx.h"
#include "FTDI_LOW_LEVEL.h"
#include "FTDI_MID_LEVEL.h"

FT_HANDLE ftHandle;
FT_STATUS ftStatus;
bool FT_OpenStatus;

int main(int argc, char *argv[])
{
	FT_DEVICE_LIST_INFO_NODE *devInfo;
	DWORD numDevs;
	DWORD devIndex = 0;
	bool FT_ShowDebugInformation = true;
	UCHAR Mask = 0xFF;
	UCHAR BitMode = 0;
	UCHAR LatencyTimer = 1;
	UCHAR FT_Byte;

	UCHAR test[31] = {1, 2, 3, 0x4, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
	UCHAR testrx[31];

	UCHAR * RxBuffer;
	UCHAR * TxBuffer;

	//File related variables
	FILE * fp;
	long  lsize;
	size_t result;
	int b;
	// time related variables
	clock_t start, stop;

//	FT_Find_all_Connected_Devices();

	FT_OpenStatus = FT_Open_By_SN(FT_ShowDebugInformation);


	ftStatus = FT_SetLatencyTimer(ftHandle, LatencyTimer);
	if (ftStatus == FT_OK)
	{

	}

	ftStatus = FT_GetLatencyTimer(ftHandle, &LatencyTimer);
	if (ftStatus == FT_OK)
	{
		printf("LatencyTimer = %d\n",LatencyTimer);
	}

	//View current FTDI bitmode settings
	FT_GetConfiguration();

	// To configure FTDI in reset mode use 		- FT_BITMODE_RESET
	// To configure FTDI in asynch bitmode use	- FT_BITMODE_ASYNC_BITBANG
	// To configure FTDI in MPSSE use		- FT_BITMODE_MPSSE
	// To configure FTDI in Synch mode		- FT_BITMODE_SYNC_FIFO
	FT_SetConfiguration(Mask, FT_BITMODE_SYNC_FIFO, FT_ShowDebugInformation);

/*
	FT_SendBuffer(test, 8, 31);
	FT_ReadBuffer(testrx, 8, 31);

	for(b = 0; b < 31; b = b + 1)
	{
		printf("Received byte 0x%x\n", testrx[b]);
	}
*/

//	FT_ProcessFile("lena512.bmp");
//	FT_ProcessFile("test.txt");
	FT_ProcessFile("test_img.JPG", "Received_image.jpg");
	// Close FTDI port
	FT_Close(ftHandle);
}
