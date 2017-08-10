#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../ftd2xx.h"
#include "FTDI_LOW_LEVEL.h"
//#include "FTDI_MID_LEVEL.h"

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
	UCHAR LatencyTimer = 5;
	UCHAR FT_Byte;

	UCHAR test[31] = {1, 2, 3, 0x4, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
	UCHAR * RxBuffer;
	UCHAR * TxBuffer;

	//File related variables
	FILE * fp;
	long  lsize;
	size_t result;

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


	//Open txt file and send content
	fp = fopen("test_data.txt", "rb");
	if (fp == NULL)
	{
		printf("test_data.txt file is not opened\n");
	}

	// find out how long file size is
	fseek(fp, 0, SEEK_END);
	lsize = ftell(fp);
	// go to file begginig othervise no data will be read out
	rewind(fp);
	printf("file size %d\n",lsize);

	// dynamic memory allocation for receive and transmit buffers
	TxBuffer = (char*) malloc (sizeof(char)*lsize);
	RxBuffer = (char*) malloc (sizeof(char)*lsize);

	if (TxBuffer == NULL)
	{
		printf("Could not allocate File_array");
	}

	result = fread(TxBuffer, 1, lsize, fp);

	fclose(fp);

	clock_t	begin = clock();
	FT_SendBuffer(TxBuffer, lsize, lsize);
	clock_t end = clock();

	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("clocks per sec %i\n", CLOCKS_PER_SEC);
	printf("time spent in ms:  %f\n", 1000*time_spent);

	start = clock();
	FT_ReadBuffer(RxBuffer, lsize, lsize);
	stop = clock();

	fp = fopen("received_data.txt", "w+");
	fwrite(RxBuffer, 1, lsize, fp);
	fclose(fp);

//	free(File_array);

	// Close FTDI port
	FT_Close(ftHandle);
}
