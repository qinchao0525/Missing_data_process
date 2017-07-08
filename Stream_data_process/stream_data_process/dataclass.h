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
	double jingdu;
	double weidu;
	double high;
	int iff;
public:
	DataClass()
	{
		jingdu = 0; weidu = 0;
		high = 0; iff=0;
	}
	bool IsFull();//ÅÐ¶ÏÊÇ·ñÊÇÍê±¸Êý¾
	bool Pointdef();
	bool Iffdef();
	bool Alldef();//ÅÐ¶ÏÊÇ·ñÊÇÊý¾ÝÈ«²¿È±Ê§
	void datadelete()//É¾³ýÊý¾Ý
	{
		jingdu = 0; weidu = 0;
		high = 0; iff=0;
	}
	void Setj(double j) { jingdu = j; }
	void Setw(double w) { weidu = w; }
	void Seth(double h) { high = h; }
	void Seti(int i) { iff = i; }
	double getj() { return jingdu; }
	double getw() { return weidu; }
	double geth() { return high; }
	int geti() { return iff; }
};

#endif // !DATACLASS_H_
#pragma once
