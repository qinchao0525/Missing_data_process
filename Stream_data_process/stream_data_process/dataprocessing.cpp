/**********************************************
Project: Missing data processing
Usage: The main function.
Auther: Qinchao
Latest modfiying time:2017/6/27
***********************************************/
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include "graypre.h"
#include "dataclass.h"
#include "interpolation.h"
#include "comparison.h"

const int N 2000;
int main()
{
//////////////////////////////////////////////////////////////////////
	std::vector<double> Jingdu;
	std::vector<double> Weidu;
	std::vector<double> High;
	std::vector<int> iff;
///////////////////////////////read data stream///////////////////////////
//	int i=0;
//	while (cin >> line)
//	{
//		i++;
//		switch (i % 4) {
//		case 1: Jingdu.push_back(atoi(line.c_str()));break;
//		case 2: Weidu.push_back(line);break;          
//		case 3: High.push_back(atof(line.c_str()));break;
//		case 0: iff.push_back(atof(line.c_str()));break;
//		}
//	}
///////////////////////////////
	DataClass dataclass[N];
	datanum=N;
	for (int i = 0; i < datanum; i++)
	{
		dataclass[i].Setj(Jingdu[i]);
		dataclass[i].Setw(High[i]);
		dataclass[i].Seth(Mod[i]);
	}
////////////////////////////////////////////////////////////////////
	std::vector<int> flag(datanum);
	for (int f = 0; f < datanum; f++)
	{
		if (dataclass[f].IsFull())
			flag[f] = 0;//
		else if (dataclass[f].Pointdef())
			flag[f] = 1;//
		else if (dataclass[f].Iffdef())
			flag[f] = 2;//
		else if (dataclass[f].Alldef())
			flag[f] = 3;//
	}
	//for (int ii = 0; ii < 100; ii++)
	//	std::cout << flag[ii] << "\t";
	for (int i = 0; i < datanum; i++)
	{
		if (flag[i] == 0)
			continue;
		else if (flag[i] == 1)//
		{
			if (dataclass[i].getj() == -1)
				interpolations(dataclass[i], 0, dataclass, datanum, flag);
			else if (dataclass[i].getw() == -1)
				interpolations(dataclass[i], 1, dataclass, datanum, flag);
			else
				interpolations(dataclass[i], 2, dataclass, datanum, flag);
		}
		else if (flag[i] == 2)//
		{
			
		}
		else if (flag[i] == 3)//
		{
			
		}
	}
	
	

	int l = 0;
	while (cout << dataclass[l].getj() << "\t" << dataclass[l].get_w()  << "\t" 
		        << dataclass[l].geth() << "\t"   << dataclass[l].geti() << "\t" )
	{
		l++;
		if (l >= N)//datanum)
			break;
	}
	return 0;
}
