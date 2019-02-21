#ifndef _LCD1602_H_YAOWU_
#define _LCD1602_H_YAOWU_

#include "reg51.h"

#ifndef uint
#define uint unsigned int
#endif
#ifndef uchar
#define uchar unsigned char
#endif

#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

void LCDInit();
void SetLCDData(uchar );
void SetLCDCommand(uchar );
void LCDLineputs(uchar ,char * source);

#endif