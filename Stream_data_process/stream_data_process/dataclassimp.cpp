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
	bool s = (jingdu != -1) && (weidu != -1) && (high != -1) && (iff != -1);
	if (s)
		return true;
	else
		return false;
}
bool DataClass::Pointdef()
{
	bool s = (jingdu == -1) || (weidu == -1) || (high == -1);
	bool ss = (jingdu == -1) && (weidu == -1) && (high == -1);
	if ( s && !ss)
		return true;
	else
		return false;
}
bool DataClass::Iffdef()
{
	if ( iff==-1 )
		return true;
	else
		return false;
}

bool DataClass::Alldef()
{
	bool s = (jingdu == -1) && (weidu == -1) && (high == -1) && (iff == -1);
	if (s)
		return true;
	else
		return false;
}
