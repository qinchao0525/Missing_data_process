/**********************************************
Project: Missing data processing
Usage: The implement of function checkread.
Auther: Qinchao
Modfiying time:2016/12/6
***********************************************/
#ifndef CHECKTABREAD_H_
#define CHECKTABREAD_H_
#include <vector>
#include <fstream>
#include <string>
#include "dataclass.h"
/*
函数名：checkread
作用：读取先验电台知识
输入：
std::vector<DataClass> &dt ------- 类数组，用来存储先验电台知识
int d ------ 先验电台的数量
输出：
输出为空，修改后的值以类数组的形势抛出
*/

void checkread(std::vector<DataClass> &dt, int d)
{
	std::vector<int> Num_c;
	std::vector<std::string> TZ_c;
	std::vector<double> F_c;
	std::vector<double> BW_c;
	std::vector<std::string> Mod_c;
	std::vector<double> P_c;
	std::vector<double> Jingdu_c;
	std::vector<double> Weidu_c;
	std::vector<double> High_c;
	std::string line_c;
	int i = 0;
	std::ifstream fin;
	fin.open("CheckTab.txt");
	while (fin >> line_c)
	{
		i++;
		switch (i % 9) {
		case 1: Num_c.push_back(atoi(line_c.c_str()));break;
		case 2: TZ_c.push_back(line_c);break;                  //string
		case 3: F_c.push_back(atof(line_c.c_str()));break;
		case 4:BW_c.push_back(atof(line_c.c_str()));break;
		case 5:Mod_c.push_back(line_c);break;                 //string
		case 6:P_c.push_back(atof(line_c.c_str()));break;
		case 7:Jingdu_c.push_back(atof(line_c.c_str()));break;
		case 8:Weidu_c.push_back(atof(line_c.c_str()));break;
		case 0:High_c.push_back(atof(line_c.c_str()));break;
		}
	}
	fin.close();
	for (int j = 0; j < d; j++)
	{
		dt[j].Setnum(Num_c[j]);
		dt[j].Set_tz(TZ_c[j]);
		dt[j].Setf(F_c[j]);
		dt[j].Setbw(BW_c[j]);
		dt[j].Set_mod(Mod_c[j]);
		dt[j].Setp(P_c[j]);
		dt[j].Setj(Jingdu_c[j]);
		dt[j].Setw(Weidu_c[j]);
		dt[j].Seth(High_c[j]);
	}
}

#endif // !CHECKTABREAD_H_

#pragma once
