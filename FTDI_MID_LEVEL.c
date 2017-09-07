
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
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

bool FT_ProcessFile(UCHAR* fileName, UCHAR* ReceivedFileName)
{
	clock_t start_t, end_t, total_t;
	long elapsed;

	// File related variables
	FILE* fp = fopen(fileName, "rb");
	long lsize;
	size_t result;

	int nPageSize = 512;
	UCHAR * RxFileBuffer;
	UCHAR * TxFileBuffer;
	UCHAR TxBuffer[nPageSize];
	UCHAR RxBuffer[nPageSize];

	if (fp != NULL)
	{
		int TxBytes = 0;

		start_t = clock();
		// find file size
		fseek(fp, 0, SEEK_END);
		lsize = ftell(fp);
//		printf("lsize :%d", lsize);
		rewind(fp);

		// dynamic memory allocation for RX and TX buffer
		TxFileBuffer = (char*) malloc (sizeof(char)*lsize);
		RxFileBuffer = (char*) malloc (sizeof(char)*lsize);

		// TO-DO implement dividing file into pagesize and check if such amount of memory can be allocated by your system

		result = fread(TxFileBuffer, 1, lsize, fp);

		//close  file
		fclose(fp);

		end_t = clock();
		total_t = ((double)end_t - start_t) * 1000 / CLOCKS_PER_SEC;
		printf("elapsed time in: %d\n", total_t);

		start_t = clock();
		while(TxBytes != lsize)
		{
			// Check if nPageSize is larger than transmitting portion of received buffer.
			if ((lsize - TxBytes) > nPageSize)
			{
				memcpy(TxBuffer, &TxFileBuffer[TxBytes], nPageSize);
				FT_SendBuffer(TxBuffer, nPageSize, nPageSize);
				FT_ReadBuffer(RxBuffer, nPageSize, nPageSize);
				memcpy(&RxFileBuffer[TxBytes], RxBuffer, nPageSize);
//				printf("nPageSize value: %d\n", lsize - TxBytes);
				TxBytes = TxBytes + nPageSize;
			}
			else
			{
				memcpy(TxBuffer, &TxFileBuffer[TxBytes], (lsize - TxBytes));
				FT_SendBuffer(TxBuffer, (lsize - TxBytes), (lsize - TxBytes));
				FT_ReadBuffer(RxBuffer, (lsize - TxBytes), (lsize - TxBytes));
				memcpy(&RxFileBuffer[TxBytes], RxBuffer, (lsize - TxBytes));
//				printf("odd nPageSize value: %d\n", lsize - TxBytes);
				TxBytes = TxBytes + (lsize - TxBytes);
			}
		};

		end_t = clock();
                total_t = ((float)end_t - start_t) * 1000 / CLOCKS_PER_SEC;
                printf("elapsed time in: %d\n", total_t);

		start_t = clock();
		fp = fopen(ReceivedFileName, "w+");
		fwrite(RxFileBuffer, 1, lsize, fp);
		fclose(fp);
		free(RxFileBuffer);
		free(TxFileBuffer);
                end_t = clock();
                total_t = ((float)end_t - start_t) * 1000 / CLOCKS_PER_SEC;
                printf("elapsed time in: %d\n", total_t);
	}
}
