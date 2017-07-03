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
��������spaceknn
���ã��Կռ������ȱʧ���ݽ���knn���
���룺
DataClass &dc ------ ȱʧ������
int i ------ ȱʧ��������ԭʼ���ݼ��е�λ�ã���������ʱ�����ʵ����ʱ��㣩
int n ------ ȱʧ����0-ͨ������ȱʧ��1-Ƶ��ȱʧ��2-����ȱʧ��3-���Ʒ�ʽȱʧ��4-����ȱʧ
std::vector<DataClass> &vdc ------ ����������
int vdc_num ------ �������Ԫ�ظ���
std::vector<int> &f) ------ ��ʾflag�����ݵı�־λ����
int z_num ------ Ϊ���վ����Ŀ
�����
���Ϊ�գ��޸ĺ��������ԭȱʧ�������׳�
*/
void spaceknn(DataClass &dc, int i, int n, std::vector<DataClass> &vdc, int vdc_num, std::vector<int> &f, int z_num)
{
	int e_num = vdc_num / z_num;
	int kk = i - (dc.getnum() - 1) * e_num;//ȱʧ���ݵ����λ�ã���Ϊ�Ժ���޸�ʱ����Ϊ���
	int dc_n = i / e_num + 1;//�ڼ������վ
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
