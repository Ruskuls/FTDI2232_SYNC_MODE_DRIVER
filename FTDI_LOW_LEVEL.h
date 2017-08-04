#ifndef FTDI_LOW_LEVEL_H_INCLUDED
#define FTDI_LOW_LEVEL_H_INCLUDED

void FT_Find_all_Connected_Devices(void);
bool FT_Open_By_SN(bool FT_ShowDebugInformation);
bool FT_SetConfiguration(UCHAR Mask, UCHAR FT_MODE, bool FT_ShowDebugInformation);
UCHAR FT_GetConfiguation(bool FT_ShowDebugInformation);
bool FT_SendByte(UCHAR cValue, bool FT_ShowDebugInformation);
bool FT_SendBuffer(UCHAR* pTxBuffer, int nPageSize, int nBufferSize);
UCHAR FT_ReadByte();

#endif
