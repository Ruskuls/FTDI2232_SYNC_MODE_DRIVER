#ifndef FTDI_LOW_LEVEL_H_INCLUDED
#define FTDI_LOW_LEVEL_H_INCLUDED

void FT_Find_all_Connected_Devices(void);
void FT_Open_By_SN(void);
void FT_SetConfiguration(UCHAR Mask, UCHAR FT_MODE);
void FT_GetConfiguation(void);
bool FT_SendByte(UCHAR cValue);

#endif
