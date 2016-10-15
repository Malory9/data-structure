#include<iostream>
#include<functional>
#include <vector>
using namespace std;

function<int(int)> Pair(int first, int second)
{
	auto innerFunc = [=](int flag)
	{
		int innerFir = first;
		int innerSec = second;

		switch (flag)
		{
		case 0:return first;
		case 1:return second;
		default:throw new std::exception;
		};
	};


	return innerFunc;

}

int GetFirst(function<int(int)>pair)
{
	return pair(0);

}
int GetSecond(function<int(int)>pair)
{
	return pair(1);
}


template class vector<int>;
