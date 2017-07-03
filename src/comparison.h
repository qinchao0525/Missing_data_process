/**********************************************
Project: Missing data processing
Usage: The implement of function conparison.
Auther: Qinchao
Modfiying time:2016/12/6
***********************************************/
#ifndef COMPARISON_H_
#define COMPARISON_H_
# include <string>
# include <fstream>
# include <vector>
# include "checktabRead.h"
/*
*/
void comparison_pro(DataClass &ddc, std::vector<DataClass> dd, int ddnum)
{
	int n=0;
	int k = 0;
	//开始对比，寻找最合适的数据集
	for (int i = 0; i < ddnum; i++) //
	{
		if ((ddc.getf() == dd[i].getf() || ddc.getf() == -1) && (ddc.getbw() == dd[i].getbw() || ddc.getbw() == -1) &&
			(ddc.get_mod() == dd[i].get_mod() || ddc.get_mod() == "-1") && (ddc.get_tz() == dd[i].get_tz() || ddc.get_tz() == "-1") && (ddc.getp() == dd[i].getp() || ddc.getp() == -1) &&
			(ddc.getj() == dd[i].getj() || ddc.getj() == -1) && (ddc.getw() == dd[i].getw() || ddc.getw() == -1) &&
			(ddc.geth() == dd[i].geth() || ddc.geth() == -1))
		{
			n++;
			k = i;
		}
	}

	if (n > 1 || n == 0)//0表示没有，此时的处理是选择删除
	{
		ddc.datadelete();
		return;
	}
	//对数据进行填充
	{
		if (ddc.getbw() == -1)
			ddc.Setbw(dd[k].getbw());
		if (ddc.getf() == -1)
			ddc.Setf(dd[k].getf());
		if (ddc.getmod() == -1)
			ddc.Set_mod(dd[k].get_mod());/////////////////////////////////////////
		if (ddc.gettz() == -1)
			ddc.Set_tz(dd[k].get_tz());
		if (ddc.getp() == -1)
			ddc.Setp(dd[k].getp());
		if (ddc.getj() == -1)
			ddc.Setj(dd[k].getj());
		if (ddc.getw() == -1)
			ddc.Setw(dd[k].getw());
		if (ddc.geth() == -1)
			ddc.Seth(dd[k].geth());
	}
}

#endif // !COMPARISON_H_

#pragma once
