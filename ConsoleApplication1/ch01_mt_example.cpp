// ConsoleApplication1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

struct t_status
{
	bool exit_main;
	bool exit_mthread;
	bool end_mthread;
	bool end_sthread1;
	bool end_sthread2;
	bool end_sthread3;
};

using namespace std;

mutex values_mtx;
mutex cout_mtx;
t_status state_info = {}; // init all members to zero(false)

int randGen(const int& min, const int& max)
{
	errno_t err;
	unsigned int number;
	int rand_no;

	err = rand_s(&number);

	rand_no = ((double)number / ((double)UINT_MAX + 1) * (double)max) + min;
	
	return rand_no;

	int loop_no = atoi("100");
}

int setTimer(clock_t & tv, long ms)
{
	if (ms > 0)
	{
		clock_t start_time = clock();
		tv = start_time + (CLOCKS_PER_SEC / 1000) * ms;
		return 0;
	}
	else
	{
		return -1;
	}
}

bool checkTimer(clock_t & tv)
{
	clock_t now;
	now = clock();
	if (now >= tv)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void threadFnc(int tid)
{
	cout_mtx.lock();
	cout << "Starting thread " << tid << "." << endl;
	cout_mtx.unlock();

	for ( ;true; )
	{
		Sleep(50);

		if (state_info.end_sthread1 == true)
		{
			state_info.end_sthread1 = false;
			break;
		}
		if (state_info.end_sthread2 == true)
		{
			state_info.end_sthread2 = false;
			break;
		}
		if (state_info.end_sthread3 == true)
		{
			state_info.end_sthread3 = false;
			break;
		}
	}
	cout_mtx.lock();
	cout << "Eng thread " << tid << "." << endl;
	cout_mtx.unlock();

	return;
}

int main_Function(int tid)
{
	thread * sub_tr1;
	thread * sub_tr2;
	thread * sub_tr3;
	clock_t limit_time;

	/*
	sub_tr1 = new thread();
	*sub_tr1 = thread(threadFnc, 11);
	
	sub_tr2 = new thread();
	*sub_tr2 = thread(threadFnc, 12);

	sub_tr3 = new thread();
	*sub_tr3 = thread(threadFnc, 13);
	*/

	setTimer(limit_time, 5000);
	for (; true; )
	{
		if (state_info.exit_mthread == true)
		{
			state_info.exit_mthread = false;
			printf("main thread exits with exit(-1)\n");
			exit(-1);
		}

		if (state_info.end_mthread == true)
		{
			state_info.end_mthread = false;
			/*
			if (sub_tr1 != NULL)
			{
				delete sub_tr1;
				sub_tr1 = NULL;
			}
			
			if (sub_tr2 != NULL)
			{
				delete sub_tr2;
				sub_tr2 = NULL;
			}
			
			if (sub_tr3 != NULL)
			{
				delete sub_tr3;
				sub_tr3 = NULL;
			}
			printf("main thread kills 3 sub threads and do exit(0)\n");
			*/
			return 0;
		}
		
		if (checkTimer(limit_time) == true)
		{
			setTimer(limit_time, 5000);
			cout << "Exit_Main: " << state_info.exit_main << ", Exit_m_thread: " << state_info.exit_mthread
				<< ", End_m_thread: " << state_info.end_mthread << ", end_sub_thread1: " << state_info.end_sthread1
				<< ", end_sub_thread2: " << state_info.end_sthread2 << ", end_sub_thread3: " << state_info.end_sthread3 << endl;
			printf("------------main thread-------------------\n");
		}
	}
	printf("This line is supposed to be unreachable(main thread).\n");

	return -1;
}

int main()
{
	int ch;
	clock_t limit_time;

	thread tr1(main_Function, 10); // launch main thread
	
	setTimer(limit_time, 5000);

	for (; true; )
	{
		ch = _getch();

		switch (ch)
		{
		case 'Q' :
			state_info.exit_main = true;
			tr1.detach();
			break;
		case 'M' :
			state_info.exit_mthread = true;
			break;
		case 'm' :
			state_info.end_mthread = true;
			break;
		case '1' :
			state_info.end_sthread1 = true;
			break;
		case '2' :
			state_info.end_sthread2 = true;
			break;
		case '3' :
			state_info.end_sthread3 = true;
			break;
		}

		if (checkTimer(limit_time) == true)
		{
			setTimer(limit_time, 5000);
			cout << "Exit_Main: " << state_info.exit_main << ", Exit_m_thread: " << state_info.exit_mthread
				<< ", End_m_thread: " << state_info.end_mthread << ", end_sub_thread1: " << state_info.end_sthread1
				<< ", end_sub_thread2: " << state_info.end_sthread2 << ", end_sub_thread3: " << state_info.end_sthread3 << endl;
			printf("------------------------------------------\n");
		}
		
		if (state_info.exit_main == true)
		{
			printf("main exits with return -1\n");
			return -1;
		}
	}
	printf("This line is supposed to be unreachable(main).\n");

	return 0;
}
