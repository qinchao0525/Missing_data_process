/**********************************************
Project: Missing data processing
Usage: The main function.
Auther: Qinchao
Latest modfiying time:2016/12/5
***********************************************/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "graypre.h"
#include "dataclass.h"
#include "interpolation.h"
#include "spaceKnn.h"
#include "checktabRead.h"
#include "comparison.h"

const unsigned int numlimit=1000000//limit of data

int main()
{
	std::cout << "���ݴ�����:\n";
////////////////////�ļ��Ķ�ȡ�����ݵĹ�һ��//////////////////////////////////////////////////
	std::vector<int> Num;
	std::vector<std::string> TZ;
	std::vector<double> F;
	std::vector<int> BW;
	std::vector<std::string> Mod;
	std::vector<double> P;
	std::vector<double> Jingdu;
	std::vector<double> Weidu;
	std::vector<double> High;
	std::string line;
	int i = 0, k = 0;
	//
	std::ifstream fin;
	fin.open("Data1.txt");
	while (fin >> line)
	{
		i++;
		switch (i % 9) {
		case 1: Num.push_back(atoi(line.c_str()));break;
		case 2: TZ.push_back(line);break;                  //string
		case 3: F.push_back(atof(line.c_str()));break;
		case 4:BW.push_back(atof(line.c_str()));break;
		case 5:Mod.push_back(line);break;                 //string
		case 6:P.push_back(atof(line.c_str()));break;
		case 7:Jingdu.push_back(atof(line.c_str()));break;
		case 8:Weidu.push_back(atof(line.c_str()));break;
		case 0:High.push_back(atof(line.c_str()));break;
		}
	}
	fin.close();
	int datanum = Num.size();
	int nd = datanum / 4;//�ĸ����վ
	std::vector<double> TZ_1(TZ.size());
	std::vector<double> Mod_1(Mod.size());
	//��string����ʹ�����ֱ�ʾ��Ƶ����Ƶ����ƵȡƵ��
	for (int p = 0; p < datanum; p++)
	{
		if (TZ[p] == "-1")
			TZ_1[p] = -1;
		else
			TZ_1[p] = (double)count(TZ.begin(), TZ.end(), TZ[p]) / TZ.size();
	}
	//AM,FM,QPSK,8QAM,4FSK,ȡƵ��
	for (int pm = 0; pm < datanum; pm++)
	{
		if (Mod[pm] == "-1")
			Mod_1[pm] = -1;
		else
			Mod_1[pm] = (double)count(Mod.begin(), Mod.end(), Mod[pm]) / Mod.size();
	}
	//ת�����ݵ���������ȥ
	std::vector<DataClass> dataclass(datanum);
	for (int i = 0; i < datanum; i++)
	{
		dataclass[i].Setnum(Num[i]);
		dataclass[i].Settz(TZ_1[i]);
		dataclass[i].Setf(F[i]);
		dataclass[i].Setbw(BW[i]);
		dataclass[i].Setmod(Mod_1[i]);
		dataclass[i].Setp(P[i]);
		dataclass[i].Setw(Weidu[i]);
		dataclass[i].Setj(Jingdu[i]);
		dataclass[i].Seth(High[i]);
		dataclass[i].Set_tz(TZ[i]);
		dataclass[i].Set_mod(Mod[i]);
	}
////////////////////��̨����֪ʶ���ȡ/////////////////////////////////////
	const int dt_num = 9;
	std::vector<DataClass> diantai(dt_num);
	checkread(diantai, dt_num);//�˺�diantai�����а����������̨֪ʶ

///////��ȡ������ϣ���ϢΪNum��TZ_1��F��BW��Mod_1��P��Jingdu��Weidu��High//////
/*
    ��ԭʼ���ݼ����л���,0-�����걸��1-ʱ����������ݲ���ȱʧ��2-�ռ���������ݲ���ȱʧ��3-ʱ��ռ����������ȱʧ��
	4-ʱ�����������ȫ��ȱʧ��5-�ռ����������ȫ��ȱʧ��6-ʱ��ռ����������ȫ��ȱʧ��
*/
	std::vector<int> flag(datanum);
	for (int f = 0; f < datanum; f++)
	{
		if (dataclass[f].IsFull())
			flag[f] = 0;//0-�����걸
		else if (dataclass[f].Timedatadef())
			flag[f] = 1;//1-ʱ����������ݲ���ȱʧ
		else if (dataclass[f].Spacedatadef())
			flag[f] = 2;//2-�ռ���������ݲ���ȱʧ
		else if (dataclass[f].TSdatadef())
			flag[f] = 3;//3-ʱ�䡢�ռ���������ݲ���ȱʧ
		else if (dataclass[f].Talldef())
			flag[f] = 4;//4-ʱ�����������ȫ��ȱʧ
		else if (dataclass[f].Salldef())
			flag[f] = 5;//5-�ռ����������ȫ��ȱʧ
		else
			flag[f] = 6;//6-����ȫ��ȱʧ
	}
	for (int ii = 0; ii < 100; ii++)
		std::cout << flag[ii] << "\t";
	/*	std::cout << dataclass[7].getf() << "\n";
	std::cout << dataclass[7].Spacedatadef() << "\n";*/
////�Բ�ͬ������µ����ݽ��в�ͬ�Ĵ�������ͬ������ݵ��ж��Ǹ���flag�е�ֵ��
	for (int i = 0; i < datanum; i++)
	{
		if (flag[i] == 0)
			continue;
		else if (flag[i] == 1)//ʱ����������ݲ���ȱʧ������λ��0��1��2�ֱ�������ȣ�γ�ȣ��߶�
		{
			if (dataclass[i].getj() == -1)
				interpolations(dataclass[i], 0, dataclass, datanum, flag);
			else if (dataclass[i].getw() == -1)
				interpolations(dataclass[i], 1, dataclass, datanum, flag);
			else
				interpolations(dataclass[i], 2, dataclass, datanum, flag);
		}
		else if (flag[i] == 2)//�ռ���������ݲ���ȱʧ����, 0��1��2��3��4�ֱ�������ƣ�Ƶ�ʣ�������ģʽ�͹���
		{
			if (dataclass[i].gettz() == -1)
				spaceknn(dataclass[i], i, 0, dataclass, datanum, flag, 4);
			else if (dataclass[i].getf() == -1)
				spaceknn(dataclass[i], i, 1, dataclass, datanum, flag, 4);
			else if (dataclass[i].getbw() == -1)
				spaceknn(dataclass[i], i, 2, dataclass, datanum, flag, 4);
			else if (dataclass[i].getmod() == -1)
				spaceknn(dataclass[i], i, 3, dataclass, datanum, flag, 4);
			else
				spaceknn(dataclass[i], i, 4, dataclass, datanum, flag, 4);
		}
		else if (flag[i] == 3)//ʱ��ռ���������ݾ�����ȱʧ
		{
			comparison_pro(dataclass[i], diantai, 9);
		}
		else if (flag[i] == 4)//ʱ�����������ȫ��ȱʧ
		{
			int n = 6;
			double a[6];
			relations(dataclass[i], 0, dataclass, datanum, flag, a, n);

			dataclass[i].Setj(GM_returnk_1(a, n));
			relations(dataclass[i], 1, dataclass, datanum, flag, a, n);
			dataclass[i].Setw(GM_returnk_1(a, n));
			relations(dataclass[i], 2, dataclass, datanum, flag, a, n);
			dataclass[i].Seth(GM_returnk_1(a, n));
		}
		else if (flag[i] == 5)//�ռ����������ȫ��ȱʧ
			continue;
		else
			dataclass[i].datadelete();
	}
	
	

	//���
	std::ofstream fout;
	fout.open("Dataout.txt");
	int l = 0;
	//std::cout << "\n";
	while (fout << dataclass[l].getnum() << "\t" << dataclass[l].get_tz()  << "\t" 
		        << dataclass[l].getf() << "\t"   << dataclass[l].getbw() << "\t" 
		        << dataclass[l].get_mod() << "\t"<< dataclass[l].getp()   << "\t" 
		        << dataclass[l].getj()   << "\t" << dataclass[l].getw()   << "\t" 
		        << dataclass[l].geth() << "\n")
	{
		l++;
		if (l >= 100)//datanum)
			break;
	}
	fout.close();
	std::cout << "\n������ϣ�" << std::endl;
/*	std::cout << "�ֶ�����һ��ȱʧ���ݼ��� \n" << std::endl;
	DataClass sd_data;
	std::cin >> sd_data.Settz;*/


	system("pause");
	return 0;
}