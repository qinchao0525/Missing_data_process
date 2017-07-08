#include <iostream>
#include <cerrno>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "GenerateGaussNoise.h"
#include "predef.h"
using namespace std;

#define ERR_EXIT(m)\
        do\
	{\
	    perror(m);\
            exit(EXIT_FAILURE);\
        }while(0)

double generateGaussianNoise(double mu, double sigma);
typedef struct data
{
	double longitude;
	double latitude;
	double high;
	int    iff; 
}IFF_data;

IFF_data info[3];


int main(int argc, char* argv[])
{
	//test options.
	if(argc<3)
	{
		cout<<"usage: "<<argv[0]<<" -kb rate.\n";
		ERR_EXIT("wrong use.");
	}
	double rate=atof(argv[2]);
	int temp=getopt(argc, argv, "kb");

	if(temp==-1)
	{
		cout<<"getopt error!"<<endl;
		ERR_EXIT("getopt");
	}
	if(temp!=-1)
	{
		switch((char)temp)
		{
			case 'k':
				rate*=1024;
				break;
			case 'b':
				break;
			defaulet:
				cout<<"wrong optiong \n";
				break;
		}
	}
	double mr;
	//cout<<"Please enter the missing rate(precision 0.00): ";
	cin>>mr;
	mr*=100;

	//init info[3]
	info[0].longitude = 124.333;
	info[0].latitude  = 20.493;
	info[0].high      = 13500;
	info[0].iff       = 0;

	info[1].longitude = 116.319;
	info[1].latitude  = 24.994;
	info[1].high      = 7515;
	info[1].iff       = 1;

	info[2].longitude = 119.086;
	info[2].latitude  = 23.765;
	info[2].high      = 11250;
	info[2].iff       = 1;

	//cout<<"start outing..."<<endl;
	int i;
	srand(time(NULL));
	//time utime
	long time=1000*1000*sizeof(IFF_data)/rate;
	//out data with input data rate.
	while(1)
	{
		usleep(time);
		i=rand()%3;
		missout(info[i].longitude+generateGaussianNoise(0,1), mr);
		missout(info[i].latitude+generateGaussianNoise(0,1), mr);
		missout(info[i].high+generateGaussianNoise(0,1), mr);
		missout(info[i].iff, mr);
	}	
	return 0;
}
