#include "Sonar.h"

float WEIGHT = 0.017;	//权值.这里不需要改动.除非你看懂原理

void Sonar_Sleep10us(uint times)
{
	unsigned char a,b;
	while(times--){
	for(b=1;b>0;b--)
		for(a=2;a>0;a--);
	}
}

void Sonar_OverFlow() interrupt 1	//INT0:0 T0:1 INT1:2 T1:3
{
	TH0 = 0;
	TL0 = 0;
}

void Sonar_Precision(float Temperature)	//利用温度与晶振修正距离
{
	float speed=0,Time=12/OCXO;	//机器周期=晶振周期*12=(1/晶振频率)*12 单位是us
	speed = (331.4 + 0.607 * Temperature);	//速度与温度的关系
	//距离 = (速度 * 时间) / 2	下面的 Time 是单位!不是时间!!!
	//权值 = (speed*100 * (时间*Time)/1000000) / 2	  统一单位为 cm/s
	WEIGHT = (speed*Time)/20000; 
}

void Sonar_Init(void)
{
	TMOD = 0x01;	//模式1的计时间
	TH0 = 0;
	TL0 = 0;			//计时器
	ET0 = 1;		//响应中断
	TR0 = 0;		//运行控制位
	EA = 1;			//总中断
}

void Sonar_Trig(void)
{
	TRIG = 1;
	Sonar_Sleep10us(1);	//10us
	TRIG = 0;
}

void Sonar_Echo(void)
{
	while(!ECHO);	//ECHO到高电平 开始计时
	TR0 = 1;	//开始计时
	while(ECHO);	//ECHO到低电平 结束计时
	TR0 = 0;	//关闭计时
}

float Sonar_Distance(void)
{
	uint Time = 0;
	float Distance=0;
	Sonar_Trig();	// 发出探测信号
	Sonar_Echo();	// 检测回声时长
	Time |= (TH0 << 8);
	Time |= TL0;		//获取时间
	TH0 = 0;	//清空计时器
	TL0 = 0;
	Sonar_Sleep10us(850);		//延时85ms,调值可以超声波垂直地面.微调直到距离为 0
	Distance = Time * WEIGHT;		//运算结果的单位是 cm
	return Distance<500?Distance:0;	//距离 = 高电平时间 * 声速(340M/S) / 2
}



