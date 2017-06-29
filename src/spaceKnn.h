/**********************************************
Project: Missing data processing
Usage: The implement of function spaceknn.
Auther: Qinchao
Latest modfiying time:2016/12/6
***********************************************/
#ifndef SPACEKNN_H_
#define SPACEKNN_H_
#include <vector>
#include "dataclass.h"
/*
函数名：spaceknn
作用：对空间相关性缺失数据进行knn填充
输入：
DataClass &dc ------ 缺失数据项
int i ------ 缺失数据所在原始数据集中的位置（后续加入时间后其实就是时间点）
int n ------ 缺失属性0-通信体制缺失，1-频率缺失，2-带宽缺失，3-调制方式缺失，4-功率缺失
std::vector<DataClass> &vdc ------ 数据类数组
int vdc_num ------ 类数组的元素个数
std::vector<int> &f) ------ 表示flag，数据的标志位数组
int z_num ------ 为侦查站的数目
输出：
输出为空，修改后的数据以原缺失数据类抛出
*/
void spaceknn(DataClass &dc, int i, int n, std::vector<DataClass> &vdc, int vdc_num, std::vector<int> &f, int z_num)
{
	int e_num = vdc_num / z_num;
	int kk = i - (dc.getnum() - 1) * e_num;//缺失数据的相对位置，可为以后可修改时间作为标尺
	int dc_n = i / e_num + 1;//第几个侦查站
	//std::cout << kk;
	switch (n)
	{
	case 0: {
		int nn = 0;
		double sum = 0;
		for (int i = 0; i < z_num; i++)
		{
			if (vdc[i*e_num + kk].gettz() != -1 && i != dc_n)
			{
				dc.Set_tz(vdc[i*e_num + kk].get_tz());
				break;
			}
		}
	};
		break;
	case 1: {
		int nn = 0;
		double sum = 0;
		for (int i = 0; i < z_num; i++)
		{
			if (vdc[i*e_num + kk].getf() != -1 && i != dc_n)
			{
				sum += vdc[i*e_num + kk].getf();
				nn++;
			}
			dc.Setf(sum / nn);
		}
	};
		break;
	case 2: {
		int nn = 0;
		double sum = 0;
		for (int i = 0; i < z_num; i++)
		{
			if (vdc[i*e_num + kk].getbw() != -1 && i != dc_n)
			{
				sum += vdc[i*e_num + kk].getbw();
				nn++;
				dc.Setbw(vdc[i*e_num + kk].getbw());
			}
			dc.Setbw(sum / nn);
		}
	};
		break;
	case 3: {
		int nn = 0;
		double sum = 0;
		for (int i = 0; i < z_num; i++)
		{
			if (vdc[i*e_num + kk].getmod() != -1 && i != dc_n)
			{
				dc.Set_mod(vdc[i*e_num + kk].get_mod());
				break;
			}
		}
	};
		break;
	case 4: {
		int nn = 0;
		double sum = 0;
		for (int i = 0; i < z_num; i++)
		{
			if (vdc[i*e_num + kk].getp() != -1 && i != dc_n)
			{
				sum += vdc[i*e_num + kk].getp();
				nn++;
			}
			dc.Setp(sum / nn);
		}
	};
		break;
	default:
		break;
	}
}

#endif // !SPACEKNN_H_

#pragma once
