#ifndef CRC_H
#define CRC_H
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#define POL9 0x07
typedef unsigned char byte;

/*!
 * \file
 * \brief plik przechowujący funkcje odpowiadające za odczytywanie i sprawdzanie integralności danych otrzymanych z mikrokontrolera
 */

int cut(int crc);
unsigned int CRC8_SingleByte(unsigned int);
byte CRC_8_Array(byte*, byte);
bool ParseDataFrame (const char*, int&, int&);


#endif // CRC_H
