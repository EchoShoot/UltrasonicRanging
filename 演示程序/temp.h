#ifndef _temp_H_
#define _temp_H_

#include "reg51.h"

#ifndef uchar 
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit Signal=P3^7;

uchar Ds18b20Init();
uchar Ds18b20ReadByte();
void  Ds18b20WriteByte(uchar MyData);
void Ds18b20ChangTemp();
void Ds18b20ReadTempCom();
int Ds18b20ReadTemp();

#endif