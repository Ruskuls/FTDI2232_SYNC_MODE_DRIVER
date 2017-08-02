#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "../ftd2xx.h"
#include "FTDI_LOW_LEVEL.h"

FT_HANDLE ftHandle;
FT_STATUS ftStatus;


void FT_Find_all_Connected_Devices(void)
{
	FT_DEVICE_LIST_INFO_NODE *devInfo;
	DWORD numDevs;
	DWORD devIndex = 0;

	// create the device information list
	ftStatus = FT_CreateDeviceInfoList(&numDevs);

	if (ftStatus == FT_OK)
	{
		printf("Number of connected devices is %d\n",numDevs);
	}

	if (numDevs > 0)
	{
		//allocate storage for list based on numDevs
		devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);

		//get the device informtion list
		ftStatus = FT_GetDeviceInfoList(devInfo, &numDevs);
		if (ftStatus == FT_OK)
		{
			for (DWORD i = 0; i < numDevs; i++)
			{
				printf(" Dev %d:\n",i);
				printf(" Flags=0x%x\n",devInfo[i].Flags);
				printf(" Type=0x%x\n",devInfo[i].Type);
				printf(" ID=0x%x\n",devInfo[i].ID);
				printf(" LocId=0x%x\n",devInfo[i].LocId);
				printf(" SerialNumber=%s\n",devInfo[i].SerialNumber);
				printf(" Description=%s\n",devInfo[i].Description);
				printf(" ftHandle=0x%x\n",devInfo[i].ftHandle);
			}
		}
	}
}

void FT_Open_By_SN(void)
{

	ftStatus = FT_OpenEx("FT17MPR0A",FT_OPEN_BY_SERIAL_NUMBER, &ftHandle);

	if (ftStatus != FT_OK)
	{
		printf("FT open failed");
		printf("Can't finde FTDI device with specified SN\n");
	}
	else
	{
		printf("FTDI for FPGA is found\n");
	}
}

//calling this function configure FTDI. Full functionality is not implemented yet
void FT_SetConfiguration(UCHAR Mask, UCHAR FT_MODE)
{

	//configure FTDI for using in Syncronous mode, up to 480Mbps
	ftStatus = FT_SetBitMode(ftHandle, Mask, FT_MODE);
	if (ftStatus == FT_OK)
	{
		printf("FTDI is configured SYNC FIFO\n");
	}
}

//Get information of selected FTDI configuration information. CPU,Syn FIFI, Async FIFO
void FT_GetConfiguration(void)
{
	UCHAR BitMode = 6;

	ftStatus = FT_GetBitMode(ftHandle, &BitMode);

	if (ftStatus == FT_OK)
	{
		printf("BitMode=%x\n",BitMode);
	}
}

bool FT_SendByte(UCHAR cValue)
{
	DWORD BytesWritten;

	ftStatus = FT_Write(ftHandle, &cValue, 1, &BytesWritten);
	if (ftStatus == FT_OK)
	{
		printf(" FT_Write Ok, sent byte 0x%x\n", cValue);
		return true;
	}
	else
	{
		printf("FT_Write Failed\n");
		return false;
	}
}


