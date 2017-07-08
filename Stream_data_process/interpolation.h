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
		//����ȱʧ������
		if (f[p_1] != 0)
		{
			R[p_1] = 0;
			continue;
		}
		//�������ϵ��cov_x
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
	//�ж���������֪���걸��������ԣ����С��80%����Ϊ��������
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
��������relations
���ã������ݵ����ϵ���������Ժ����ĻҶ�Ԥ����׼������
���룺
DataClass &dc ------ ȱʧ������
int n ------ ȱʧ��
std::vector<DataClass> &vdc ------ ����������
int vdc_num ------ �������Ԫ�ظ���
std::vector<int> &f) ------ ��ʾflag�����ݵı�־λ����
double a[] ------ ��ȱʧ���������ϵ��������������
int a_num ------ ������������ݸ���
�����
�����ϵ����ߵ�a_num��������ϵ��ֵ����a[]�У�ͨ���������׳�a[]
*/
void relations(DataClass &dc, //ȱʧ������
	int n,//ȱʧ��
	std::vector<DataClass> &vdc,//����������
	int vdc_num,/*�������Ԫ�ظ���*/
	std::vector<int> &f,//��ʾflag
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
		//����ȱʧ������
		if (f[p_1] != 0)
		{
			R[p_1] = 0;
			continue;
		}
		//�������ϵ��cov_x
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
