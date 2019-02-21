#include "reg51.h"
#include "LCD1602.h"
#include "Sonar.h"
#include "temp.h"
#include <stdio.h>

float GetTemperature (void)
{
	float Temperature = (float)Ds18b20ReadTemp();
	return (Temperature>0?Temperature:-Temperature) * 0.0625;	//得到温度
}

void main(void)
{
	char line1[16]="";
	char line2[16]="";
	float Temperature=0;
	
	Sonar_Init();	//初始化超声波
	LCDInit();	//初始化LCD
	
	while(1)
	{
		Temperature = GetTemperature();	//获取温度
		Sonar_Precision(Temperature,12);	//修正声呐(温度,晶振)
		sprintf(line1,"Temp:%+07.2fC",Temperature);
		sprintf(line2,"Dist:%+07.2fcm",Sonar_Distance());
		LCDLineputs(1,line1);
		LCDLineputs(2,line2);
	}
}