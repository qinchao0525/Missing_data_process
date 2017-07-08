#include <iostream>
using std::cout;

template<class T>
void missout(T num, int mr)
{	
	int i=rand()%101;
	if(i<=mr)
		cout<<-1<<" ";
	else
		cout<<num<<" "; 
}
