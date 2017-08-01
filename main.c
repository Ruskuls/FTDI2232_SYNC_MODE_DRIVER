#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../ftd2xx.h"
#include "FTDI_LOW_LEVEL.h"

FT_HANDLE ftHandle;
FT_STATUS ftStatus;

int main(int argc, char *argv[])
{
	FT_DEVICE_LIST_INFO_NODE *devInfo;
	DWORD numDevs;
	DWORD devIndex = 0;
	UCHAR Mask = 0xff;
	UCHAR FT_MODE_SYNC_FIFO = 1;
	UCHAR BitMode=6;

	FT_Open_By_SN();

/*
	//Configure FTDI for using in Synchronous mode, up to 480Mbps
	ftStatus = FT_SetBitMode(ftHandle, Mask, FT_MODE_SYNC_FIFO);
	if (ftStatus == FT_OK)
	{
		printf("FTDI is configured SYNC FIFO\n");
	}

	ftStatus = FT_GetBitMode(ftHandle, &BitMode);
	if (ftStatus == FT_OK)
	{
		printf("BitMode=%d\n",BitMode);
	}
*/

	FT_GetConfiguration();
	// Configure FTDI in Synch mode
	FT_SetConfiguration(FT_MODE_SYNC_FIFO);



	// Close FTDI port
	FT_Close(&ftHandle);
}
