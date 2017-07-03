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
////��ֵ��亯��
/*
��������interpolations
���ã������ݽ��в�ֵ���
���룺
DataClass &dc ------ ȱʧ������
int dc_num ------ ȱʧ����λ��0��1��2�ֱ�����ȣ�γ�ȣ��߶�
std::vector<DataClass> &vdc ------ ����������
int vdc_num ------ �������Ԫ�ظ���
std::vector<int> &f) ------ ��ʾflag�����ݵı�־λ����
�����
���Ϊ�գ��޸ĺ��������ԭȱʧ�������׳�
*/
void interpolations(DataClass &dc, //ȱʧ������
	int dc_num, //ȱʧ����λ��0��1��2�ֱ�����ȣ�γ�ȣ��߶�
	std::vector<DataClass> &vdc,//����������
	int vdc_num/*�������Ԫ�ظ���*/,
	std::vector<int> &f)//��ʾflag
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
	//�ж���������֪���걸��������ԣ����С��80%����Ϊ��������
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
