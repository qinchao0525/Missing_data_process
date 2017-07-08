/**********************************************
Project: Missing data processing
Usage: The main function.
Auther: Qinchao
Latest modfiying time:2017/7/7
***********************************************/
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include "graypre.h"
#include "dataclass.h"
#include "interpolation.h"
using namespace std;
const int N = 2000;
const int CACHE = 5;
bool readable=false;
int index = 0;
//void handler(int signo)
//{
//}

int main()
{
//////////////////////////////////////////////////////////////////////
	vector<vector<double> > Jingdu(CACHE);
	for(int i=0; i<CACHE; i++)
		Jingdu[i].resize(N);
	vector<vector<double> > Weidu(CACHE);
	for(int i=0; i<CACHE; i++)
		Weidu[i].resize(N);
	vector<vector<double> > High(CACHE);
	for(int i=0; i<CACHE; i++)
		High[i].resize(N);
	vector<vector<int> > iff(CACHE);
	for(int i=0; i<CACHE; i++)
		iff[i].resize(N);
///////////////////////////////read data stream///////////////////////////
	pid_t pid;
	pid=fork();
	double line;
	if(pid==0)
	{
		int br=0;
		while(1)
		{
			int ii=0;
			while (cin >> line)
			{	
				ii++;
				switch (ii % 4) {
					case 1: Jingdu[br][ii]=line;break;
					case 2: Weidu[br][ii]=line;break;          
					case 3: High[br][ii]=line;break;
					case 0: iff[br][ii]=line;break;
				}
				if(ii>=N)
				{
					readable=true;
					index=br;
					break;
				}
			}	
			br++;
			if(br==5)
				br=0;
		}
	}
///////////////////////////////////////////////////////////////////////////
	while(1)
	{
		if(readable==true)
		{
		
			vector<DataClass> dataclass(N);
			for (int i = 0; i < N; i++)
			{
				dataclass[i].Setj(Jingdu[index][i]);
				dataclass[i].Setw(Weidu[index][i]);
				dataclass[i].Seth(High[index][i]);
				dataclass[i].Seti(iff[index][i]);
			}
////////////////////////////////////////////////////////////////////
			std::vector<int> flag(N);
			for (int f = 0; f < N; f++)
			{
				if (dataclass[f].IsFull())
					flag[f] = 0;//
				else if (dataclass[f].Pointdef())
					flag[f] = 1;//
				else if (dataclass[f].Iffdef())
					flag[f] = 2;//
				else if (dataclass[f].Palldef())
					flag[f] = 3;
				else if (dataclass[f].Alldef())
					flag[f] = 4;//
			}

			for (int i = 0; i < N; i++)
			{
				if (flag[i] == 0)
					continue;
				else if (flag[i] == 1)//
				{
					if (dataclass[i].getj() == -1)
					{
						int n=6;
						double a[6];
						relations(dataclass[i], 0, dataclass, N, flag, a, n);
						dataclass[i].Setj(GM_returnk_1(a,n));
					}
					else if (dataclass[i].getw() == -1)
					{
						int n=6;
						double a[6];
						relations(dataclass[i], 1, dataclass, N, flag, a, n);
						dataclass[i].Setj(GM_returnk_1(a,n));
					}
					else
					{
						int n=6;
						double a[6];
						relations(dataclass[i], 2, dataclass, N, flag, a, n);
						dataclass[i].Setj(GM_returnk_1(a,n));
					}
				}
				else if (flag[i] == 2)//
				{
					interpolations(dataclass[i], dataclass, N, flag);
				}
				else if (flag[i] == 3)//
				{
					continue;
				}
				else
					continue;
			}


	
			int l = 0;
			while (cout << dataclass[l].getj() << "\t" << dataclass[l].getw()  << "\t" 
					<< dataclass[l].geth() << "\t"   << dataclass[l].geti() << "\t" )
			{
				l++;
				if (l >= N)//
					break;
			}
			readable=false;
		}
	}

	return 0;
}
