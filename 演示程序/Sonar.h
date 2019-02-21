#ifndef __SONAR_H_YAOWU__
#define __SONAR_H_YAOWU__

#ifndef uchar
#define uchar unsigned char 
#endif
#ifndef uint
#define uint unsigned int
#endif

#include <reg51.h>

sbit TRIG = P2^1;		//将这里调整下你就可以正常使用这个模块了
sbit ECHO = P2^0;

void Sonar_Init(void);				//声呐传感器初始化
void Sonar_Trig(void);
void Sonar_Echo(void);
void Sonar_Precision(float,float);	//利用温度值与晶振频率运算出声音传播速度从而修正距离
float Sonar_Distance(void);	//返回与目标的距离,这里可以较为精准测量 0.5cm ~ 5m 内的距离

#endif