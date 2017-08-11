#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "../ftd2xx.h"
#include "FTDI_LOW_LEVEL.h"
#include "FTDI_MID_LEVEL.h"

FT_HANDLE ftHandle;
FT_STATUS ftStatus;

bool FT_SendReceiveBuffer(UCHAR* TxBuffer, UCHAR* RxBuffer, int nPageSize, int nBufferSize)
{

	FT_SendBuffer(TxBuffer, nPageSize, nBufferSize);
	FT_ReadBuffer(RxBuffer, nPageSize, nBufferSize);
//	return true;
}

bool FT_ProcessFile(UCHAR* fileName)
{
	// File related variables
	FILE* fp = fopen(fileName, "rb");
	long lsize;
	size_t result;

	UCHAR * RxBuffer;
	UCHAR * TxBuffer;

	if (fp != NULL)
	{
		// find file size
		fseek(fp, 0, SEEK_END);
		lsize = ftell(fp);
		rewind(fp);

		// dynamic me mory allocation for RX and TX buffer
		TxBuffer = (char*) malloc (sizeof(char)*lsize);
		RxBuffer = (char*) malloc (sizeof(char)*lsize);

		// TO-DO implement dividing file into pagesize and check if such amount of memory can be allocated by your system

		result = fread(TxBuffer, 1, lsize, fp);

		//close  file
		fclose(fp);

		FT_SendBuffer(TxBuffer, lsize, lsize);

		FT_ReadBuffer(RxBuffer, lsize, lsize);

		fp = fopen("received_data.txt", "w+");
		fwrite(RxBuffer, 1, lsize, fp);
		fclose(fp);
	}
}
