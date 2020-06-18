#include "crc.h"

unsigned int CRC8_SingleByte(unsigned int Data2)
{
    unsigned int Poly = (POL9 << 7);
    for (byte i = 0; i < 8; ++i)
    {
        if ((Data2 & 0x8000) != 0) Data2 ^= Poly;
        Data2 <<= 1;
    }
    return Data2;
}

int cut(int crc)
{
    if(crc>=100)
        return 4;
    else if(crc<100 && crc >= 10)
        return 3;
    else
        return 2;
}

byte CRC_8_Array(byte* pData, byte Len)
{
    unsigned int Data2 = pData[0] << 8;

    for (unsigned int Idx = 1; Idx < Len; ++Idx)
    {
        Data2 |= pData[Idx];
        Data2 = CRC8_SingleByte(Data2);
    }
    Data2 = CRC8_SingleByte(Data2);
    return (byte)(Data2 >> 8);
}

bool ParseDataFrame (const char *pDataFrame, int &AccX, int &AccY)
{
    std::istringstream IStrm(pDataFrame);
    char FHeader;
    unsigned int CRC8;
    IStrm >> FHeader >> AccX >> AccY >> CRC8;
    if (IStrm.fail() || FHeader != 'X') return false;
    return (byte)CRC8 == CRC_8_Array((byte*)(pDataFrame), strlen(pDataFrame)-cut(CRC8));
}
