#include <string.h>
#include "LCD1602.h"

void LCD_Sleep1ms(uint c)
{
    uchar a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }       
	}
}

void LCDInit()
{
	SetLCDCommand(0x06);	//写入新数据光标右移,屏幕不动.
	SetLCDCommand(0x0C);	//光标不闪烁,无光标,显示功能打开.
	SetLCDCommand(0x38);	//5x7\显示两行\数据总线8根
	SetLCDCommand(0x01);	//清屏
	SetLCDCommand(0x80);	//调整光标到左上角
}

void SetLCDCommand(uchar source)
{
	LCD1602_RS = 0;	// L 命令
	LCD1602_RW = 0;	// L 写
	LCD1602_E = 0;
	
	LCD1602_DATAPINS = source;
	LCD_Sleep1ms(1);
	
	LCD1602_E = 1;
	LCD_Sleep1ms(5);
	LCD1602_E = 0;
}

void SetLCDData(uchar source)
{
	LCD1602_RS = 1;		//H 数据
	LCD1602_RW = 0;		//L 写
	LCD1602_E = 0;
	
	LCD1602_DATAPINS = source;
	LCD_Sleep1ms(1);
	
	LCD1602_E = 1;
	LCD_Sleep1ms(5);
	LCD1602_E = 0;
}


void LCDLineputs(uchar line,char * source)
{
	uchar j=0,length=strlen(source);
	line = (line==2?1:0);	//将line 转换成布尔值 0表示第一行 1 表示第二行

	if(length>16)return;	
	SetLCDCommand(line?0xC0:0x80);	//设置写入地址
	for(j=0;j<length;j++)
	{
		SetLCDData(*(source + j));
	}
}