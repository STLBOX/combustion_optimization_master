// stdafx.cpp : source file that includes just the standard includes
//	interface.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

//  ËÄÉáÎåÈë
double Round(double Num,int i)
{return int(Num*pow(10,i)+0.5)/float(pow(10,i));} 

double Sign(double x)
{
	if(x>0)
		return 1;
	else if(x==0)
		return 0;
	else
		return -1;
}

double Abs(double x)
{
	if(x>0)
		return x;
	else
		return -x;
}


double Max(double x, double y)
{
	if(x>y)
		return x;
	else
		return y;
}



