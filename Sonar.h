/*
=================作者:张耀午=================
2016年11月23日17:15:26             版本: V2.1
联系方式:                  852822425@qq.com
===========================================
v1.0 实现超声波测距
v2.0 实现基于温度与晶振频率矫正的测距方式
v2.1 改为人性化接口,无需每次修正都要输入晶振频率
-------------------------------------------
*/

#ifndef __SONAR_H_YAOWU__
#define __SONAR_H_YAOWU__

#ifndef uchar
#define uchar unsigned char 
#endif
#ifndef uint
#define uint unsigned int
#endif

//在这调整下你就可以正常使用这个模块了
#include <reg51.h>		//这里调整成:包含针脚名称的头文件
sbit TRIG = P2^1;		//Trig 针脚
sbit ECHO = P2^0;		//Echo 针脚
float OCXO = 12;		//晶振频率:12MHz

void Sonar_Init(void);				//声呐传感器初始化
void Sonar_Trig(void);				//触发信号
void Sonar_Echo(void);				//回声信号
void Sonar_Precision(float);		//利用温度值运算出当前环境声音传播速度从而修正距离
float Sonar_Distance(void); //返回与目标的距离,这里可以较为精准测量 0.5cm ~ 5m 内的距离

#endif