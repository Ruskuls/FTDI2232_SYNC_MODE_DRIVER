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

bool FT_Open_By_SN(bool FT_ShowDebugInformation)
{

	ftStatus = FT_OpenEx("FT26FFDLA",FT_OPEN_BY_SERIAL_NUMBER, &ftHandle);

	if (ftStatus != FT_OK)
	{
		if (FT_ShowDebugInformation == TRUE)
		{
			printf("FT open failed\n");
			printf("Can't finde FTDI device with specified SN\n");
		}
		return true;
	}
	else
	{
		if (FT_ShowDebugInformation == TRUE)
		{
			printf("FTDI for FPGA is found\n");
		}
		return false;
	}
}

//calling this function configure FTDI. Full functionality is not implemented yet
bool FT_SetConfiguration(UCHAR Mask, UCHAR FT_MODE, bool FT_ShowDebugInformation)
{

	//configure FTDI for using in Syncronous mode, up to 480Mbps
	ftStatus = FT_SetBitMode(ftHandle, Mask, FT_MODE);
	if (ftStatus == FT_OK)
	{
		if (FT_ShowDebugInformation == true)
		{
			printf("FTDI is configured SYNC FIFO\n");
		}
		return true;
	}
	else
	{
		return false;
	}
}

//Get information of selected FTDI configuration information. CPU,Syn FIFI, Async FIFO
UCHAR FT_GetConfiguration(bool FT_ShowDebugInformation)
{
	UCHAR BitMode;

	ftStatus = FT_GetBitMode(ftHandle, &BitMode);

	if (ftStatus == FT_OK)
	{
		if (FT_ShowDebugInformation == true)
		{
			printf("BitMode=%x\n",BitMode);
		}
		return BitMode;
	}
	else
	{
		return 0xAA;
	}
}

// This function writes to FTDI device only one byte
bool FT_SendByte(UCHAR cValue, bool FT_ShowDebugInformation)
{
	DWORD BytesWritten;

	ftStatus = FT_Write(ftHandle, &cValue, 1, &BytesWritten);
	if (ftStatus == FT_OK)
	{
		if (FT_ShowDebugInformation == true)
		{
			printf(" FT_Write Ok, sent byte 0x%x\n", cValue);
		}
		return true;
	}
	else
	{
		if (FT_ShowDebugInformation == true)
		{
			printf("FT_Write Failed\n");
		}
		return false;
	}
}

bool FT_SendBuffer(UCHAR* pTxBuffer, int nPageSize, int nBufferSize)
{
//	DWORD nBufferSize = 32;
	DWORD BytesSent;
	int nTxBuffer = 0;

	while(nPageSize !=0)
	{
		ftStatus = FT_Write(ftHandle, (char*)((int)pTxBuffer+nTxBuffer), nPageSize, &BytesSent);
		if (ftStatus == FT_OK)
		{
			if (BytesSent == nPageSize)
			{
				nTxBuffer += BytesSent;
			}
			else
			{
				nTxBuffer += BytesSent;
			}
		}
		else
		{
			printf("FT Write Failed\n");
			return false;
		}
		if ((nBufferSize - nTxBuffer) < nPageSize)
		{
			nPageSize = (nBufferSize - nTxBuffer);
		}
	}

	return true;
}

UCHAR FT_ReadByte()
{

	DWORD BytesReceived;
	UCHAR FT_Byte;

	ftStatus = FT_Read(ftHandle, &FT_Byte, 1, &BytesReceived);
	if (ftStatus == FT_OK)
	{
		return FT_Byte;
	}
	else
	{
		printf("FT_Read failed\n");
		return 0;
	}
}

bool FT_ReadBuffer(UCHAR* pRxBuffer, int nPageSize, int nBMBufferSize)
{
	DWORD nBufferSize = nBMBufferSize;
	DWORD BytesReceived;
	int nRxBuffer = 0;

	while(nPageSize != 0)
	{
		ftStatus = FT_Read(ftHandle, (UCHAR*)((int)pRxBuffer+nRxBuffer), nPageSize, &BytesReceived);
		if (ftStatus == FT_OK)
		{
			if (BytesReceived == nPageSize)
			{
				nRxBuffer += BytesReceived;
			}
			else
			{
				nRxBuffer += BytesReceived;
			}
		}
		else
		{
			printf("FT_Read Failed!\n");
			return false;
		}

		if ((nBufferSize - nRxBuffer) < nPageSize)
		{
			nPageSize = (nBufferSize - nRxBuffer);
		}
	}

	return true;
}
