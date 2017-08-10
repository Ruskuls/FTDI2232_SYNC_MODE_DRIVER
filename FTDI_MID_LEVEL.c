#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "../ftd2xx.h"
//#include "FTDI_LOW_LEVEL.c"
#include "FTDI_MID_LEVEL.h"

FT_HANDLE ftHandle;
FT_STATUS ftStatus;

bool FT_SendReceiveBuffer(UCHAR* TxBuffer, UCHAR* RxBuffer, int nPageSize, int nBufferSize)
{

	FT_SendBuffer(TxBuffer, nPageSize, nBufferSize);
	FT_ReadBuffer(RxBuffer, nPageSize, nBufferSize);
//	return true;
}

