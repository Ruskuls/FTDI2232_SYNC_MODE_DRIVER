#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "../ftd2xx.h"
#include "FTDI_LOW_LEVEL.h"

FT_HANDLE ftHandle;
FT_STATUS ftStatus;
bool FT_OpenStatus;

int main(int argc, char *argv[])
{
	FT_DEVICE_LIST_INFO_NODE *devInfo;
	DWORD numDevs;
	DWORD devIndex = 0;
	bool FT_ShowDebugInformation = false;
	UCHAR Mask = 0xFF;
	UCHAR BitMode = 0;
	UCHAR LatencyTimer = 5;
	UCHAR FT_Byte;

	UCHAR test[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

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
//	FT_SetConfiguration(Mask, FT_BITMODE_SYNC_FIFO);

	FT_SendByte(0x01, FT_ShowDebugInformation);
//	FT_SendBuffer(test, 8, 8);

	FT_Byte = FT_ReadByte();
	printf("Read value from FTDI 0x%x\n",FT_Byte);

	// Close FTDI port
	FT_Close(ftHandle);

}
