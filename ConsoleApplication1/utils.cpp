#include "stdafx.h"

/*
using namespace std;

int randGen(const int& min, const int& max)
{
	static thread_local mt19937 generator
		(hash<thread::id>() (this_thread::get_id()));

	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

ostream & operator << (ostream & output, const t_result & arg)
{
	output << "Thread id : " << arg.tid << "Value: " << arg.value << ".";
	return output;
}

*/