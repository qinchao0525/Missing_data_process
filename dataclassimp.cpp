/**********************************************
Project: Missing data processing
Usage: The implement of dataclass.
Auther: Qinchao
Latest modfiying time:2016/12/5
***********************************************/
#include <string>
#include "dataclass.h"
////num ; tz ; f ; bw ; mod ; p ; jingdu ; weidu ; high ;
bool DataClass::IsFull()
{
	bool t = (tz != -1) && (f != -1) && (bw != -1) && (mod != -1) && (p != -1);
	bool s = (jingdu != -1) && (weidu != -1) && (high != -1);
	if ( t && s )
		return true;
	else
		return false;
}
bool DataClass::Timedatadef()
{
	bool t = (tz != -1) && (f != -1) && (bw != -1) && (mod != -1) && (p != -1);
	bool s = (jingdu == -1) || (weidu == -1) || (high == -1);
	bool ss = (jingdu == -1) && (weidu == -1) && (high == -1);
	if (t && s && !ss)
		return true;
	else
		return false;
}
bool DataClass::Spacedatadef()
{
	bool t = (tz == -1) || (f == -1) || (bw == -1) || (mod == -1) || (p == -1);
	bool tt = (tz == -1) && (f == -1) && (bw == -1) && (mod == -1) && (p == -1);
	bool s = (jingdu != -1) && (weidu != -1) && (high != -1);
	return t && s && !tt;
/*	if (t && s && !t)
		return true;
	else
		return false;*/
}
bool DataClass::TSdatadef()
{
	bool t = (tz == -1) || (f == -1) || (bw == -1) || (mod == -1) || (p == -1);
	bool s = (jingdu == -1) || (weidu == -1) || (high == -1);
	if (t && s)
		return true;
	else
		return false;
}
bool DataClass::Talldef()
{
	bool t = (tz != -1) && (f != -1) && (bw != -1) && (mod != -1) && (p != -1);
	bool s = (jingdu == -1) && (weidu == -1) && (high == -1);
	if (t && s)
		return true;
	else
		return false;
}
bool DataClass::Salldef()
{
	bool t = (tz == -1) && (f == -1) && (bw == -1) && (mod == -1) && (p == -1);
	bool s = (jingdu != -1) && (weidu != -1) && (high != -1);
	return s;
/*	if (t && s)
		return true;
	else
		return false;*/
}
bool DataClass::Alldef()
{
	bool t = (tz != -1) || (f != -1) || (bw != -1) || (mod != -1) || (p != -1);
	bool s = (jingdu != -1) || (weidu != -1) || (high != -1);
	if (!t && !s)
		return true;
	else
		return false;
}