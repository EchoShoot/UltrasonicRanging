#include "temp.h"

void Ds18b20Sleep1ms(uint time)
{
	uint temp;
	for(;time>0;time--)
		for(temp=110;temp>0;temp--);
}

uchar Ds18b20Init()
{
	uint Sleep;
	Signal = 0;	//	(1).数据线拉到低电平“0”。
	Sleep=70;
	while(Sleep--);//	(2).延时480微妙（该时间的时间范围可以从480到960微妙）。
	Signal = 1;//	(3).数据线拉到高电平“1”。
	Sleep = 0;
	while(Signal)
	{
		Ds18b20Sleep1ms(1);
		Sleep++;
		if(Sleep>5)
		{
			return 0;
		} 
			
	}
	return 1;//	(5).若CPU读到了数据线上的低电平“0”后，还要做延时，其延时的时间从发出的高电平算起（第（3）步的时间算起）最少要480微妙
}

uchar Ds18b20ReadByte()
{
	uint i=0,Sleep=0;
	uchar MyData=0,temp=0;
	for(i=0;i<8;i++)
	{
		Signal = 0;//	(1).将数据线拉低“0”。
		Sleep++;//	(2).延时1微妙。
		Signal = 1;//	(3).将数据线拉高“1”,释放总线准备读数据。
		Sleep++;
		Sleep++;
		temp = Signal;
		MyData = (MyData >> 1) | (temp << 7);
		Sleep = 4;
		while(Sleep--);
	}
	return MyData;
}

void  Ds18b20WriteByte(uchar MyData)
{
	uint i=0,Sleep=0;
	for(i=0;i<8;i++)
	{
		Signal = 0;//	(1).数据线先置低电平“0”
		Sleep++;
		Signal = MyData & 0x01;//	(3).按从低位到高位的顺序发送数据(一次只发送一位)。
		Sleep=6;
		while(Sleep--);
		Signal = 1;//	(5).将数据线拉到高电平。
		MyData >>= 1;
	}
}

void Ds18b20ChangTemp()
{
	Ds18b20Init();
	Ds18b20Sleep1ms(1);
	Ds18b20WriteByte(0xcc);	//跳过搜索,直接使用
	Ds18b20WriteByte(0x44);	//温度转换命令
}

void Ds18b20ReadTempCom()
{
	Ds18b20Init();
	Ds18b20Sleep1ms(1);
	Ds18b20WriteByte(0xcc);	//跳过搜索,直接使用
	Ds18b20WriteByte(0xbe);	//发送读取温度命令
}

int Ds18b20ReadTemp()
{
	int temp = 0;
	uchar tmh,tml;
	Ds18b20ChangTemp();
	Ds18b20ReadTempCom();
	tml = Ds18b20ReadByte();		//这个问题我找了一个晚上.以后一定要记得顺序这个东西!
	tmh = Ds18b20ReadByte();		//因为 这个 tmh 与 tml 顺序反了!导致问题出现!!!
	temp |= (tmh << 8);
	temp |= tml;
	return temp;
}