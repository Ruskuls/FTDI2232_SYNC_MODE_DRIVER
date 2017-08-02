#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "../ftd2xx.h"
#include "FTDI_LOW_LEVEL.h"

FT_HANDLE ftHandle;
FT_STATUS ftStatus;

int main(int argc, char *argv[])
{
	FT_DEVICE_LIST_INFO_NODE *devInfo;
	DWORD numDevs;
	DWORD devIndex = 0;
	UCHAR Mask = 0xFF;
	UCHAR BitMode = 0;
	UCHAR LatencyTimer = 5;

	FT_Open_By_SN();

/*
	ftStatus = FT_SetLatencyTimer(ftHandle, LatencyTimer);
	if (ftStatus == FT_OK)
	{

	}
*/
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
	FT_SetConfiguration(Mask, FT_BITMODE_SYNC_FIFO);

	// Close FTDI port
	FT_Close(ftHandle);
}
