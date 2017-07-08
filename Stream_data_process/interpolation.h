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
#include <cmath>
#include "dataclass.h"

void interpolations(DataClass &dc, //
	std::vector<DataClass> &vdc,//
	int vdc_num,
	std::vector<int> &f)//
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
		sum_1 = dc.getj() + dc.getw() + dc.geth();
		cov_x = sqrt(pow(dc.getj() - sum_1 / 3, 2) + pow(dc.getw() - sum_1 / 3, 2) + pow(dc.geth() - sum_1 / 3, 2));
		//cov_y
		sum = vdc[p_1].getj() + vdc[p_1].getw() + vdc[p_1].geth();
		cov_y = sqrt(pow(vdc[p_1].getj() - sum / 3, 2) + pow(vdc[p_1].getw() - sum / 3, 2) + pow(vdc[p_1].geth() - sum / 3, 2) );
		//cov_xy
		cov_xy = (dc.getj() - sum_1 / 3)*(vdc[p_1].getj() - sum / 3) + (dc.getw() - sum_1 / 3)*(vdc[p_1].getw() - sum / 3) +
			(dc.geth() - sum_1 / 3)*(vdc[p_1].geth() - sum / 3);
		//R
		R[p_1] = abs(cov_xy / (cov_x*cov_y));
	}
	R_it = max_element(R.begin(), R.end());
	int g = R_it - R.begin();
	//判断数据与已知的完备数据相关性，如果小于80%则认为是新数据
	if (R[g] > 0.8)
	{
		dc.Seti(vdc[g].geti());
	}
	else
	{
		dc.Seti(0);
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
		sum_1 = dc.getj() + dc.getw() + dc.geth();
		cov_x = sqrt(pow(dc.getj() - sum_1 / 3, 2) + pow(dc.getw() - sum_1 / 3, 2) + pow(dc.geth() - sum_1 / 3, 2));
		//cov_y
		sum = vdc[p_1].getj() + vdc[p_1].getw() + vdc[p_1].geth();
		cov_y = sqrt(pow(vdc[p_1].getj() - sum / 3, 2) + pow(vdc[p_1].getw() - sum / 3, 2) + pow(vdc[p_1].geth() - sum / 3, 2) );
		//cov_xy
		cov_xy = (dc.getj() - sum_1 / 3)*(vdc[p_1].getj() - sum / 3) + (dc.getw() - sum_1 / 3)*(vdc[p_1].getw() - sum / 3) +
			(dc.geth() - sum_1 / 3)*(vdc[p_1].geth() - sum / 3);
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
			a[j]= vdc[i].geti();
				j++;
		}
	}
	
}

#endif // !

#pragma once
