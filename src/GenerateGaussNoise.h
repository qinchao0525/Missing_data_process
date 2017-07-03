/**********************************************
Project: Missing data processing
Usage: The function to create Gaussnoise.
Auther: Qinchao
Latest modfiying time:2016/12/5
***********************************************/
#ifndef GENERATEGAUSSNOISE_H_
#define GENERATEGAUSSNOISE_H_
# include <limits>
/*
函数名：generateGaussianNoise
作用：产生单个的高斯噪声
输入：
double mu ------ 均值

double sigma ------ 方差
输出：
单个的高斯噪声数据
*/
double generateGaussianNoise(double mu, double sigma)
{
	const double epsilon = std::numeric_limits<double>::min();
	const double two_pi = 2.0*3.14159265358979323846;

	static double z0, z1;
	static bool generate;
	generate = !generate;

	if (!generate)
		return z1 * sigma + mu;

	double u1, u2;
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);

	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
	return z0 * sigma + mu;
}
#endif // !GENERATEGAUSSNOISE_H_
#pragma once
