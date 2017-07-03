/**********************************************
Project: Missing data processing
Usage: The implement of function interpolation.
Auther: Qinchao
Modfiying time:2016/12/6
***********************************************/
#ifndef INTERPOLATION_H_
#define INTERPOLATION_H_
#include <vector>
#include <algorithm>
#include "dataclass.h"
////差值填充函数
/*
函数名：interpolations
作用：对数据进行差值填充
输入：
DataClass &dc ------ 缺失数据项
int dc_num ------ 缺失数据位置0，1，2分别代表经度，纬度，高度
std::vector<DataClass> &vdc ------ 数据类数组
int vdc_num ------ 类数组的元素个数
std::vector<int> &f) ------ 表示flag，数据的标志位数组
输出：
输出为空，修改后的数据以原缺失数据类抛出
*/
void interpolations(DataClass &dc, //缺失数据项
	int dc_num, //缺失数据位置0，1，2分别代表经度，纬度，高度
	std::vector<DataClass> &vdc,//数据类数组
	int vdc_num/*类数组的元素个数*/,
	std::vector<int> &f)//表示flag
{
	std::vector<double> R(vdc_num);
	std::vector<double>::iterator R_it;
	double cov_xy = 0;
	double cov_x = 0;
	double cov_y = 0;
	double sum_1 = 0;
	double sum = 0;
	for (int p_1 = 0; p_1 < vdc_num; p_1++)
	{
		//跳过缺失数据项
		if (f[p_1] != 0)
		{
			R[p_1] = 0;
			continue;
		}
		//计算相关系数cov_x
		sum_1 = dc.gettz() + dc.getf() + dc.getbw() + dc.getmod() + dc.getp();
		cov_x = sqrt(pow(dc.gettz() - sum_1 / 5, 2) + pow(dc.getf() - sum_1 / 5, 2) + pow(dc.getbw() - sum_1 / 5, 2) +
			pow(dc.getmod() - sum_1 / 5, 2) + pow(dc.getp() - sum_1 / 5, 2) );
		//cov_y
		sum = vdc[p_1].gettz() + vdc[p_1].getf() + vdc[p_1].getmod() + vdc[p_1].getbw() + vdc[p_1].getp();
		cov_y = sqrt(pow(vdc[p_1].gettz() - sum / 5, 2) + pow(vdc[p_1].getf() - sum / 5, 2) + pow(vdc[p_1].getmod() - sum / 5, 2) +
			pow(vdc[p_1].getbw() - sum / 5, 2) + pow(vdc[p_1].getp() - sum / 5, 2));
		//cov_xy
		cov_xy = (dc.gettz() - sum_1 / 5)*(vdc[p_1].gettz() - sum / 5) + (dc.getf() - sum_1 / 5)*(vdc[p_1].getf() - sum / 5) +
			(dc.getbw() - sum_1 / 5)*(vdc[p_1].getbw() - sum / 5) + (dc.getmod() - sum_1 / 5)*(vdc[p_1].getmod() - sum / 5) +
			(dc.getp() - sum_1 / 5)*(vdc[p_1].getp() - sum / 5);
		//R
		R[p_1] = abs(cov_xy / (cov_x*cov_y));
		//R[c].push_back(abs(cov_xy/(cov_x*cov_y)));
	}
	R_it = max_element(R.begin(), R.end());
	int g = R_it - R.begin();
	//判断数据与已知的完备数据相关性，如果小于80%则认为是新数据
	if (R[g] > 0.8)
	{
		switch (dc_num)
		{
		case 0: dc.Setj(vdc[g].getj());
			break;
		case 1: dc.Setw(vdc[g].getw());
			break;
		case 2: dc.Seth(vdc[g].geth());
			break;
		}
	}
	else
	{
		switch (dc_num)
		{
		case 0: dc.Setj(0);
			break;
		case 1: dc.Setw(0);
			break;
		case 2: dc.Seth(0);
			break;
		}
	}

}
/*
函数名：relations
作用：求数据的相关系数，用来对后续的灰度预测做准备数据
输入：
DataClass &dc ------ 缺失数据项
int n ------ 缺失项
std::vector<DataClass> &vdc ------ 数据类数组
int vdc_num ------ 类数组的元素个数
std::vector<int> &f) ------ 表示flag，数据的标志位数组
double a[] ------ 与缺失数据项相关系数最大的数据数组
int a_num ------ 数据数组的数据个数
输出：
求相关系数最高的a_num个点的相关系数值放入a[]中，通过函数内抛出a[]
*/
void relations(DataClass &dc, //缺失数据项
	int n,//缺失项
	std::vector<DataClass> &vdc,//数据类数组
	int vdc_num,/*类数组的元素个数*/
	std::vector<int> &f,//表示flag
	double a[], int a_num)
{
	std::vector<double>::iterator R_it;
	std::vector<double> R(vdc_num);
	double cov_xy = 0;
	double cov_x = 0;
	double cov_y = 0;
	double sum_1 = 0;
	double sum = 0;
	for (int p_1 = 0; p_1 < vdc_num; p_1++)
	{
		//跳过缺失数据项
		if (f[p_1] != 0)
		{
			R[p_1] = 0;
			continue;
		}
		//计算相关系数cov_x
		sum_1 = dc.gettz() + dc.getf() + dc.getbw() + dc.getmod() + dc.getp();
		cov_x = sqrt(pow(dc.gettz() - sum_1 / 5, 2) + pow(dc.getf() - sum_1 / 5, 2) + pow(dc.getbw() - sum_1 / 5, 2) +
			pow(dc.getmod() - sum_1 / 5, 2) + pow(dc.getp() - sum_1 / 5, 2));
		//cov_y
		sum = vdc[p_1].gettz() + vdc[p_1].getf() + vdc[p_1].getmod() + vdc[p_1].getbw() + vdc[p_1].getp();
		cov_y = sqrt(pow(vdc[p_1].gettz() - sum / 5, 2) + pow(vdc[p_1].getf() - sum / 5, 2) + pow(vdc[p_1].getmod() - sum / 5, 2) +
			pow(vdc[p_1].getbw() - sum / 5, 2) + pow(vdc[p_1].getp() - sum / 5, 2));
		//cov_xy
		cov_xy = (dc.gettz() - sum_1 / 5)*(vdc[p_1].gettz() - sum / 5) + (dc.getf() - sum_1 / 5)*(vdc[p_1].getf() - sum / 5) +
			(dc.getbw() - sum_1 / 5)*(vdc[p_1].getbw() - sum / 5) + (dc.getmod() - sum_1 / 5)*(vdc[p_1].getmod() - sum / 5) +
			(dc.getp() - sum_1 / 5)*(vdc[p_1].getp() - sum / 5);
		//R
		R[p_1] = abs(cov_xy / (cov_x*cov_y));
	}
	R_it = max_element(R.begin(), R.end());
	int g = R_it - R.begin();
	int j = 0;
	//std::cout << R[g];
	for (int i = 0; i < R.size(); i++)
	{
		if (R[i] == R[g])//abs(R[i] - R[g]) < 0.01)??
		{
			if (j >= a_num)
				break;
			switch (n)
			{
			case 0:a[j]= vdc[i].getj();
				j++;
				break;
			case 1:a[j] = vdc[i].getw();
				j++;
				break;
			case 2:a[j] = vdc[i].geth();
				j++;
				break;
			default:
				break;
			}
		}
	}
	for (int y = 0; y < 6; y++)
		std::cout << a[y] << "\t";
	std::cout << "\n";
}

#endif // !

#pragma once
