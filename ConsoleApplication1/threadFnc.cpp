#include "stdafx.h"

/*

using namespace std;

extern mutex values_mtx;
extern mutex cout_mtx;
extern vector<t_result> results;

void threadFnc(t_result result)
{
	cout_mtx.lock();
	cout << "Starting thread " << result.tid << "." << endl;
	cout_mtx.unlock();

	values_mtx.lock();
	int val = results[0].value;
	values_mtx.unlock();

	int rval = randGen(0, 10);
	val += rval;

	cout_mtx.lock();
	cout << "Thread " << result.tid << " adding " << rval << ". New value: "
		<< val << "." << endl;
	cout_mtx.unlock();

	values_mtx.lock();
	results.push_back({ result.tid, val });
	values_mtx.unlock();
}

*/