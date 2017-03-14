/**********************************************
Project: Missing data processing
Usage: The defination of dataclass.
Auther: Qinchao
Latest modfiying time:2016/12/5
***********************************************/
#ifndef DATACLASS_H_
#define DATACLASS_H_
#include <string>
class DataClass{
private:
	int num;
	double tz;//存储转换后的数字数据
	double f;
	double bw;
	double mod;
	double p;
	double jingdu;
	double weidu;
	double high;
	std::string _tz;//存储字符串形势的数据
	std::string _mod;//
public:
	DataClass()
	{
		num = 0; tz = 0; f = 0; bw = 0;
		mod = 0; p = 0; jingdu = 0; weidu = 0;
		high = 0;_tz = "0";_mod = "0";
	}
	bool IsFull();//判断是否是完备数据
	bool Timedatadef();//判断是否是时间相关性数据缺失
	bool Spacedatadef();//判断是否是空间相关性数据缺失
	bool TSdatadef();//判断是否是时间相关和空间相关性数据都缺失
	bool Talldef();//判断是否是时间相关性数据全部缺失
	bool Salldef();//判断是否是空间相关性数据全部缺失
	bool Alldef();//判断是否是数据全部缺失
	void datadelete()//删除数据
	{
		num = 0; tz = 0; f = 0; bw = 0;
		mod = 0; p = 0; jingdu = 0; weidu = 0;
		high = 0;
	}
	void Setnum(int n) { num = n; }
	void Settz(double t) { tz = t; }
	void Setf(double ff) { f = ff; }
	void Setbw(double b) { bw = b; }
	void Setmod(double m) { mod = m; }
	void Setp(double pp) { p = pp; }
	void Setj(double j) { jingdu = j; }
	void Setw(double w) { weidu = w; }
	void Seth(double h) { high = h; }
	void Set_tz(std::string t) { _tz = t; }
	void Set_mod(std::string o) { _mod = o; }
	int getnum() { return num; }
	double gettz() { return tz; }
	double getf() { return f; }
	double getbw() { return bw; }
	double getmod() { return mod; }
	double getp() { return p; }
	double getj() { return jingdu; }
	double getw() { return weidu; }
	double geth() { return high; }
	std::string get_tz() { return _tz; }
	std::string get_mod() { return _mod; }
};

#endif // !DATACLASS_H_
#pragma once